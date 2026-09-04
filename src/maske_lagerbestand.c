#include <stdio.h>

#include "maske_lagerbestand.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "artikel.h"
#include "maske_artikelanzeige.h"
#include "maske_fehlermeldung.h"


static void liste_zeichnen(void)
{
    char zeile[140];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("LAGERBESTAND");
    bildschirm_schreiben(2, 3, "ARTIKEL    BEZEICHNUNG                MENGE  LAGERPLATZ");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = 0; i < artikel_anzahl(); i++)
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

    bildschirm_schreiben(2, 22, "ARTIKELNUMMER:");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();
}


Ergebnis maske_lagerbestand_anzeigen(void)
{
    for (;;)
    {
        char nummer[16];

        liste_zeichnen();

        if (eingabe_zeile(nummer, sizeof(nummer), 15, 17, 22) == -1)
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
