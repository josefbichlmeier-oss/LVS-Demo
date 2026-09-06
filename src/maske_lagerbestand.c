#include <stdio.h>

#include "maske_lagerbestand.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "artikel.h"
#include "paginierung.h"
#include "maske_artikelanzeige.h"
#include "maske_fehlermeldung.h"

#define ZEILEN_PRO_SEITE 14


static void liste_zeichnen(const Paginierung *seiten)
{
    char zeile[140];
    char hinweis[40];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("LAGERBESTAND");
    bildschirm_schreiben(2, 3, "ARTIKEL    BEZEICHNUNG                MENGE  LAGERPLATZ");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = paginierung_start_index(seiten); i < paginierung_ende_index(seiten); i++)
    {
        Artikel *artikel = artikel_at(i);

        snprintf(
            zeile, sizeof(zeile),
            "%-10s %-25s %6d  %-10s",
            artikel->nummer,
            artikel->bezeichnung,
            artikel->bestand,
            artikel->lagerplatz
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    paginierung_hinweis(hinweis, sizeof(hinweis), seiten);
    bildschirm_schreiben(2, 20, hinweis);

    bildschirm_schreiben(2, 22, "ARTIKELNUMMER:");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();
}


Ergebnis maske_lagerbestand_anzeigen(void)
{
    Paginierung seiten = { 0, ZEILEN_PRO_SEITE, artikel_anzahl() };

    for (;;)
    {
        char nummer[16];

        liste_zeichnen(&seiten);

        char erste_taste = eingabe_taste();

        if (erste_taste == '+')
        {
            paginierung_naechste(&seiten);
            continue;
        }

        if (erste_taste == '-')
        {
            paginierung_vorherige(&seiten);
            continue;
        }

        if (erste_taste == '\033')
        {
            return ERG_ZURUECK;
        }

        if (eingabe_zeile_mit_erstem_zeichen(
                erste_taste, nummer, sizeof(nummer), 15, 17, 22) == -1)
        {
            return ERG_ZURUECK;
        }

        if (nummer[0] == '\0')
        {
            continue;
        }

        Artikel *artikel = artikel_finden(nummer);

        if (artikel)
        {
            maske_artikelanzeige_anzeigen(artikel);
        }
        else
        {
            maske_fehlermeldung_anzeigen("ARTIKEL NICHT GEFUNDEN");
        }
    }
}
