#include <stdio.h>

#include "maske_artikelanzeige.h"
#include "bildschirm.h"
#include "eingabe.h"


Ergebnis maske_artikelanzeige_anzeigen(const Artikel *artikel)
{
    char puffer[16];

    bildschirm_loeschen();
    bildschirm_titel("ARTIKEL");

    bildschirm_schreiben(5, 4, "ARTIKELNUMMER:");
    bildschirm_schreiben(5, 5, "BEZEICHNUNG:");
    bildschirm_schreiben(5, 6, "BESTAND:");
    bildschirm_schreiben(5, 7, "LAGERPLATZ:");
    bildschirm_aktion("ESC = ZURUECK");

    bildschirm_feld(25, 4, artikel->nummer);
    bildschirm_feld(25, 5, artikel->bezeichnung);

    snprintf(puffer, sizeof(puffer), "%d", artikel->bestand);
    bildschirm_feld(25, 6, puffer);

    bildschirm_feld(25, 7, artikel->lagerplatz);

    bildschirm_ausgeben();

    for (;;)
    {
        bildschirm_cursor(26, 26);

        char taste = eingabe_taste();

        if (taste == '\033')
        {
            return ERG_ZURUECK;
        }
    }
}
