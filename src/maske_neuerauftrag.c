#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maske_neuerauftrag.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "kunde.h"
#include "artikel.h"
#include "auftragsverwaltung.h"
#include "maske_kundenuebersicht.h"
#include "maske_artikelsuche.h"
#include "maske_fehlermeldung.h"


/* Modulzustand waehrend der laufenden Erfassung - entspricht den
 * Instanzvariablen @kunde/@artikel/@positionen der Ruby-Klasse. */
static Kunde *g_kunde;
static Artikel *g_artikel;
static Auftragsposition g_positionen[MAX_POSITIONEN];
static int g_positionen_anzahl;


static int reservierte_menge(const Artikel *artikel)
{
    int summe = 0;

    for (int i = 0; i < g_positionen_anzahl; i++)
    {
        if (strcmp(g_positionen[i].artikelnummer, artikel->nummer) == 0)
        {
            summe += g_positionen[i].menge;
        }
    }

    return summe;
}


static int bestand_verfuegbar(const Artikel *artikel, int menge)
{
    int verfuegbar = artikel->bestand - reservierte_menge(artikel);

    return menge <= verfuegbar;
}


static void zeichnen(void)
{
    char zeile[140];

    bildschirm_loeschen();
    bildschirm_titel("NEUER AUFTRAG");

    bildschirm_schreiben(2,  4, "KUNDENNUMMER:");
    bildschirm_schreiben(2,  5, "NAME:");
    bildschirm_schreiben(2,  6, "ORT:");
    bildschirm_schreiben(2,  8, "ARTIKEL  BEZEICHNUNG                       MENGE");
    bildschirm_schreiben(2,  9, "------------------------------------------------------------");
    bildschirm_schreiben(2, 17, "------------------------------------------------------------");
    bildschirm_schreiben(2, 18, "ARTIKELNUMMER:");
    bildschirm_schreiben(2, 19, "BEZEICHNUNG:");
    bildschirm_schreiben(2, 20, "BESTAND:");
    bildschirm_schreiben(2, 21, "RESERVIERT:");
    bildschirm_schreiben(2, 22, "VERFUEGBAR:");
    bildschirm_schreiben(5, 24, "WEITERE POSITION? J/N");
    bildschirm_aktion("ESC = ZURUECK");

    if (g_kunde)
    {
        char ort[48];

        bildschirm_feld(20, 4, g_kunde->nummer);
        bildschirm_feld(20, 5, g_kunde->name);

        snprintf(ort, sizeof(ort), "%s %s", g_kunde->plz, g_kunde->ort);
        bildschirm_feld(20, 6, ort);
    }

    if (g_artikel)
    {
        char puffer[16];
        int reserviert = reservierte_menge(g_artikel);

        bildschirm_feld(20, 18, g_artikel->nummer);
        bildschirm_feld(20, 19, g_artikel->bezeichnung);

        snprintf(puffer, sizeof(puffer), "%d", g_artikel->bestand);
        bildschirm_feld(20, 20, puffer);

        snprintf(puffer, sizeof(puffer), "%d", reserviert);
        bildschirm_feld(20, 21, puffer);

        snprintf(puffer, sizeof(puffer), "%d", g_artikel->bestand - reserviert);
        bildschirm_feld(20, 22, puffer);
    }

    int y = 10;

    for (int i = 0; i < g_positionen_anzahl; i++)
    {
        Artikel *artikel = artikel_finden(g_positionen[i].artikelnummer);
        const char *bezeichnung = artikel ? artikel->bezeichnung : "?";

        snprintf(
            zeile, sizeof(zeile),
            "%-8s %-30.30s %5d",
            g_positionen[i].artikelnummer,
            bezeichnung,
            g_positionen[i].menge
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    bildschirm_ausgeben();
}


/* Rueckgabe: 0 = ok (nummer_out gefuellt), -1 = abbrechen (ESC/zurueck) */
static int kundennummer_waehlen(char *nummer_out, size_t nummer_out_groesse)
{
    for (;;)
    {
        int ergebnis =
            eingabe_zeile(nummer_out, nummer_out_groesse, 20, 20, 4);

        if (ergebnis == -1)
        {
            return -1;
        }

        if (nummer_out[0] == '\0')
        {
            Ergebnis auswahl =
                maske_kundenuebersicht_anzeigen(nummer_out, nummer_out_groesse);

            if (auswahl == ERG_ZURUECK)
            {
                return -1;
            }

            zeichnen();
        }

        Kunde *kunde = kunde_finden(nummer_out);

        if (kunde)
        {
            return 0;
        }

        maske_fehlermeldung_anzeigen("KUNDE NICHT GEFUNDEN");
        zeichnen();
    }
}


/* Rueckgabe: gefundener Artikel, oder NULL bei Abbruch */
static Artikel *artikelnummer_waehlen(void)
{
    char artikelnummer[16];

    for (;;)
    {
        int ergebnis =
            eingabe_zeile(artikelnummer, sizeof(artikelnummer), 15, 20, 18);

        if (ergebnis == -1)
        {
            return NULL;
        }

        if (artikelnummer[0] == '\0')
        {
            Ergebnis auswahl =
                maske_artikelsuche_anzeigen(artikelnummer, sizeof(artikelnummer));

            if (auswahl == ERG_ZURUECK)
            {
                return NULL;
            }

            zeichnen();
        }

        Artikel *artikel = artikel_finden(artikelnummer);

        if (artikel)
        {
            return artikel;
        }

        maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
        zeichnen();
    }
}


Ergebnis maske_neuerauftrag_anzeigen(Auftrag **erstellter_auftrag_out)
{
    char kundennummer[16];
    char menge_puffer[16];
    char weiter_puffer[16];

    g_kunde = NULL;
    g_artikel = NULL;
    g_positionen_anzahl = 0;

    zeichnen();

    if (kundennummer_waehlen(kundennummer, sizeof(kundennummer)) == -1)
    {
        return ERG_ZURUECK;
    }

    g_kunde = kunde_finden(kundennummer);

    zeichnen();

    if (!g_kunde)
    {
        maske_fehlermeldung_anzeigen("KUNDE NICHT GEFUNDEN");
        return ERG_ZURUECK;
    }

    g_positionen_anzahl = 0;

    for (;;)
    {
        g_artikel = artikelnummer_waehlen();

        if (!g_artikel)
        {
            return ERG_ZURUECK;
        }

        zeichnen();

        if (eingabe_zeile(menge_puffer, sizeof(menge_puffer), 15, 20, 21) == -1)
        {
            return ERG_ZURUECK;
        }

        int menge = atoi(menge_puffer);

        if (!bestand_verfuegbar(g_artikel, menge))
        {
            maske_fehlermeldung_anzeigen("BESTAND NICHT AUSREICHEND");
            continue;
        }

        if (g_positionen_anzahl < MAX_POSITIONEN)
        {
            strncpy(
                g_positionen[g_positionen_anzahl].artikelnummer,
                g_artikel->nummer,
                sizeof(g_positionen[g_positionen_anzahl].artikelnummer) - 1
            );
            g_positionen[g_positionen_anzahl].artikelnummer[
                sizeof(g_positionen[g_positionen_anzahl].artikelnummer) - 1
            ] = '\0';

            g_positionen[g_positionen_anzahl].menge = menge;
            g_positionen_anzahl++;
        }
        else
        {
            maske_fehlermeldung_anzeigen("MAXIMALE POSITIONSANZAHL ERREICHT");
        }

        g_artikel = NULL;

        zeichnen();

        if (eingabe_zeile(weiter_puffer, sizeof(weiter_puffer), 15, 27, 24) == -1)
        {
            return ERG_ZURUECK;
        }

        if (toupper((unsigned char)weiter_puffer[0]) == 'N')
        {
            break;
        }
    }

    Auftrag *auftrag = auftrag_neu(kundennummer);

    if (!auftrag)
    {
        maske_fehlermeldung_anzeigen("AUFTRAG KONNTE NICHT ANGELEGT WERDEN");
        return ERG_ZURUECK;
    }

    for (int i = 0; i < g_positionen_anzahl; i++)
    {
        auftrag_position_hinzufuegen(
            auftrag,
            g_positionen[i].artikelnummer,
            g_positionen[i].menge
        );
    }

    *erstellter_auftrag_out = auftrag;

    return ERG_OK;
}
