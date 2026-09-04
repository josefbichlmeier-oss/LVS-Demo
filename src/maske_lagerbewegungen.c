#include <ctype.h>
#include <stdio.h>

#include "maske_lagerbewegungen.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "lagerbewegungsbestand.h"
#include "artikel.h"


void maske_lagerbewegungen_anzeigen(void)
{
    char zeile[140];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("LAGERBEWEGUNGEN");
    bildschirm_schreiben(2, 3, "ARTIKEL BEZEICHNUNG               MENGE VORGANG");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    /* jüngste zuerst - Ruby iteriert Lagerbewegungsbestand.alle.reverse */
    for (int i = lagerbewegungs_anzahl() - 1; i >= 0; i--)
    {
        Lagerbewegung *bewegung = lagerbewegung_at(i);
        Artikel *artikel = artikel_finden(bewegung->artikelnummer);

        const char *bezeichnung =
            artikel ? artikel->bezeichnung : "UNBEKANNT";

        int menge_signiert =
            (bewegung->typ == LAGER_AUSGANG) ? -bewegung->menge : bewegung->menge;

        const char *vorgang =
            (bewegung->typ == LAGER_AUSGANG) ? "WARENAUSGANG" : "WARENEINGANG";

        snprintf(
            zeile, sizeof(zeile),
            "%-6s  %-24s %+6d %-20s",
            bewegung->artikelnummer,
            bezeichnung,
            menge_signiert,
            vorgang
        );

        bildschirm_feld(2, y, zeile);
        y++;

        if (y > 23)
            break;
    }

    bildschirm_aktion("X  ZURUECK");
    bildschirm_ausgeben();

    for (;;)
    {
        char taste = (char)toupper((unsigned char)eingabe_taste());

        if (taste == 'X')
        {
            return;
        }
    }
}
