#include <ctype.h>

#include "eingabe.h"
#include "tastatur.h"
#include "bildschirm.h"


void eingabe_init(void)
{
    tastatur_init();
}


char eingabe_taste(void)  { return tastatur_lesen(); }
char eingabe_warten(void) { return tastatur_lesen(); }
char eingabe_lesen(void)  { return tastatur_lesen(); }


/*
 * Verarbeitet genau ein bereits gelesenes Zeichen im Kontext einer
 * laufenden eingabe_zeile()-Eingabe (Echo, Backspace, CR, ESC).
 *
 * Rueckgabe:  0 = weiter Zeichen lesen
 *             1 = fertig (CR/Enter)
 *            -1 = abgebrochen (ESC)
 */
static int zeile_zeichen_verarbeiten(
    char taste,
    char *puffer,
    size_t puffer_groesse,
    int max_laenge,
    int x,
    int y,
    int *laenge
)
{
    if (taste == '\r' || taste == '\n')
    {
        bildschirm_dunkel();
        return 1;
    }

    if (taste == '\033')
    {
        bildschirm_dunkel();
        puffer[0] = '\0';
        return -1;
    }

    if (taste == '\b' || taste == 0x7F)
    {
        if (*laenge > 0)
        {
            (*laenge)--;
            puffer[*laenge] = '\0';

            bildschirm_schreiben(x + *laenge, y, " ");
            bildschirm_ausgeben();
            bildschirm_cursor(x + *laenge, y);
        }

        return 0;
    }

    if (*laenge < max_laenge &&
        (size_t)(*laenge + 1) < puffer_groesse)
    {
        char zeichen = (char)toupper((unsigned char)taste);
        char einzel[2];

        puffer[*laenge] = zeichen;
        (*laenge)++;
        puffer[*laenge] = '\0';

        einzel[0] = zeichen;
        einzel[1] = '\0';

        bildschirm_schreiben(x + *laenge - 1, y, einzel);
        bildschirm_ausgeben();
    }

    return 0;
}


int eingabe_zeile(
    char *puffer,
    size_t puffer_groesse,
    int max_laenge,
    int x,
    int y
)
{
    int laenge = 0;
    int ergebnis;

    puffer[0] = '\0';

    bildschirm_hell();
    bildschirm_cursor(x, y);

    for (;;)
    {
        char taste = eingabe_taste();

        ergebnis = zeile_zeichen_verarbeiten(
            taste, puffer, puffer_groesse, max_laenge, x, y, &laenge
        );

        if (ergebnis != 0)
        {
            break;
        }
    }

    return (ergebnis == -1) ? -1 : 0;
}


int eingabe_zeile_mit_erstem_zeichen(
    char erstes_zeichen,
    char *puffer,
    size_t puffer_groesse,
    int max_laenge,
    int x,
    int y
)
{
    int laenge = 0;
    int ergebnis;

    puffer[0] = '\0';

    bildschirm_hell();
    bildschirm_cursor(x, y);

    ergebnis = zeile_zeichen_verarbeiten(
        erstes_zeichen, puffer, puffer_groesse, max_laenge, x, y, &laenge
    );

    while (ergebnis == 0)
    {
        char taste = eingabe_taste();

        ergebnis = zeile_zeichen_verarbeiten(
            taste, puffer, puffer_groesse, max_laenge, x, y, &laenge
        );
    }

    return (ergebnis == -1) ? -1 : 0;
}


int eingabe_passwort(
    char *puffer,
    size_t puffer_groesse,
    int max_laenge
)
{
    int laenge = 0;

    puffer[0] = '\0';

    for (;;)
    {
        char taste = eingabe_taste();

        if (taste == '\r' || taste == '\n')
        {
            break;
        }

        if (taste == '\033')
        {
            puffer[0] = '\0';
            return -1;
        }

        if (taste == '\b' || taste == 0x7F)
        {
            if (laenge > 0)
            {
                laenge--;
                puffer[laenge] = '\0';
            }

            continue;
        }

        if (laenge < max_laenge &&
            (size_t)(laenge + 1) < puffer_groesse)
        {
            puffer[laenge] = (char)toupper((unsigned char)taste);
            laenge++;
            puffer[laenge] = '\0';
        }
    }

    return 0;
}
