#include <stdio.h>
#include <string.h>

#include "../config/config.h"
#include "bildschirm.h"
#include "terminal.h"
#include "zeit_port.h"


typedef struct
{
    int  x;
    int  y;
    char text[D621_BREITE + 1];
    int  ist_feld;

} Aenderung;


static char daten[D621_HOEHE][D621_BREITE + 1];

static Aenderung aenderungen[D621_MAX_AENDERUNGEN];
static int aenderungen_anzahl = 0;

/* Wird gesetzt, wenn mehr Aenderungen anfielen, als der Puffer
 * fasst - in dem Fall wird bei ausgeben() sicherheitshalber der
 * komplette Bildschirm neu gesendet statt nur der Aenderungsliste. */
static int ueberlauf = 0;


static void puffer_leeren(void)
{
    for (int y = 0; y < D621_HOEHE; y++)
    {
        for (int x = 0; x < D621_BREITE; x++)
        {
            daten[y][x] = ' ';
        }
        daten[y][D621_BREITE] = '\0';
    }
}


static void aenderung_merken(int x, int y, const char *text, int ist_feld)
{
    if (aenderungen_anzahl >= D621_MAX_AENDERUNGEN)
    {
        ueberlauf = 1;
        return;
    }

    Aenderung *eintrag = &aenderungen[aenderungen_anzahl];

    eintrag->x = x;
    eintrag->y = y;
    eintrag->ist_feld = ist_feld;

    strncpy(eintrag->text, text, D621_BREITE);
    eintrag->text[D621_BREITE] = '\0';

    aenderungen_anzahl++;
}


static void puffer_schreiben(int x, int y, const char *text)
{
    if (y < 0 || y >= D621_HOEHE)
        return;

    for (int i = 0; text[i] != '\0'; i++)
    {
        int xpos = x + i;

        if (xpos < 0)
            continue;

        if (xpos >= D621_BREITE)
            break;

        daten[y][xpos] = text[i];
    }
}


void bildschirm_init(void)
{
    puffer_leeren();

    aenderungen_anzahl = 0;
    ueberlauf = 0;
}


void bildschirm_loeschen(void)
{
    terminal_loeschen();

    puffer_leeren();

    aenderungen_anzahl = 0;
    ueberlauf = 0;
}


void bildschirm_schreiben(int x, int y, const char *text)
{
    puffer_schreiben(x, y, text);
    aenderung_merken(x, y, text, 0);
}


void bildschirm_feld(int x, int y, const char *text)
{
    puffer_schreiben(x, y, text);
    aenderung_merken(x, y, text, 1);
}


void bildschirm_linie(int y)
{
    static char linie_puffer[D621_BREITE + 1];

    for (int i = 0; i < D621_BREITE; i++)
    {
        linie_puffer[i] = '-';
    }
    linie_puffer[D621_BREITE] = '\0';

    bildschirm_schreiben(0, y, linie_puffer);
}


void bildschirm_titel(const char *text)
{
    char zeit_puffer[24];
    int laenge = (int)strlen(text);
    int x = (D621_BREITE - laenge) / 2;

    if (x < 0)
        x = 0;

    bildschirm_schreiben(x, 0, text);

    zeit_text(zeit_puffer, sizeof(zeit_puffer));

    bildschirm_schreiben(D621_BREITE - 17, 0, zeit_puffer);

    bildschirm_linie(1);
}


void bildschirm_status(const char *text, const char *zustand)
{
    char zeile[D621_BREITE + 1];
    int rechts_laenge = (int)strlen(zustand);
    int links_breite = D621_BREITE - rechts_laenge - 2;
    int i = 0;

    if (links_breite < 0)
        links_breite = 0;

    for (; i < links_breite && text[i] != '\0'; i++)
    {
        zeile[i] = text[i];
    }
    for (; i < links_breite; i++)
    {
        zeile[i] = ' ';
    }

    for (int j = 0; j < rechts_laenge && i < D621_BREITE; j++, i++)
    {
        zeile[i] = zustand[j];
    }

    zeile[i] = '\0';

    bildschirm_feld(0, D621_HOEHE - 1, zeile);
}


void bildschirm_aktion(const char *text)
{
    char puffer[21];
    int i = 0;

    for (; i < 20 && text[i] != '\0'; i++)
    {
        puffer[i] = text[i];
    }
    for (; i < 20; i++)
    {
        puffer[i] = ' ';
    }
    puffer[20] = '\0';

    bildschirm_schreiben(10, D621_HOEHE - 1, puffer);
}


void bildschirm_cursor(int x, int y)
{
    /* Direkter, sofortiger Terminalbefehl - entspricht exakt Ruby
     * Bildschirm#cursor, das @terminal.position(x,y) unmittelbar
     * aufruft (kein Zusammenhang mit dem Dirty-Tracking/@geaendert
     * und nicht erst bei ausgeben() wirksam). */
    terminal_position(x, y);
}


void bildschirm_cursor_zurueck(void)
{
    terminal_cursor_zurueck();
}


void bildschirm_hell(void)
{
    terminal_hell();
}


void bildschirm_dunkel(void)
{
    terminal_dunkel();
}


static void alles_senden(void)
{
    for (int y = 0; y < D621_HOEHE; y++)
    {
        terminal_position(0, y);
        terminal_schreiben(daten[y]);
    }
}


void bildschirm_ausgeben(void)
{
    if (ueberlauf)
    {
        alles_senden();
    }
    else
    {
        for (int i = 0; i < aenderungen_anzahl; i++)
        {
            Aenderung *eintrag = &aenderungen[i];

            terminal_position(eintrag->x, eintrag->y);

            if (eintrag->ist_feld)
                terminal_hell();

            terminal_schreiben(eintrag->text);

            if (eintrag->ist_feld)
                terminal_dunkel();
        }
    }

    aenderungen_anzahl = 0;
    ueberlauf = 0;

    /*
     * Bewusst KEIN erneutes Positionieren des Cursors hier - das
     * Original tut das an dieser Stelle ebenfalls nicht (die dafuer
     * vorgesehenen Instanzvariablen werden dort nirgends gesetzt).
     * Nach dem Schreiben eines einzelnen Zeichens steht der
     * Terminal-Cursor bereits durch den natuerlichen Vorschub des
     * Terminals (Hazeltine wie ANSI-VT) automatisch richtig - siehe
     * bildschirm_cursor() fuer die Faelle, in denen explizit
     * repositioniert werden muss (z.B. nach Backspace).
     */
}
