#include <ctype.h>
#include <stdio.h>

#include "maske_lagerbewegungen.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "lagerbewegungsbestand.h"
#include "artikel.h"
#include "paginierung.h"

#define ZEILEN_PRO_SEITE 18


static void liste_zeichnen(const Paginierung *seiten)
{
    char zeile[140];
    char hinweis[40];
    int y = 5;
    int gesamt = lagerbewegungs_anzahl();

    bildschirm_loeschen();
    bildschirm_titel("LAGERBEWEGUNGEN");
    bildschirm_schreiben(2, 3, "ARTIKEL BEZEICHNUNG               MENGE VORGANG");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    /* j laeuft ueber die Anzeigereihenfolge (juengste zuerst - Ruby
     * iteriert Lagerbewegungsbestand.alle.reverse); i ist der
     * zugehoerige Index im tatsaechlichen (chronologischen) Array. */
    for (int j = paginierung_start_index(seiten); j < paginierung_ende_index(seiten); j++)
    {
        int i = gesamt - 1 - j;

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
    }

    paginierung_hinweis(hinweis, sizeof(hinweis), seiten);
    bildschirm_schreiben(2, 24, hinweis);

    bildschirm_aktion("X  ZURUECK");
    bildschirm_ausgeben();
}


void maske_lagerbewegungen_anzeigen(void)
{
    Paginierung seiten = { 0, ZEILEN_PRO_SEITE, lagerbewegungs_anzahl() };

    for (;;)
    {
        liste_zeichnen(&seiten);

        char taste = (char)toupper((unsigned char)eingabe_taste());

        if (taste == '+')
        {
            paginierung_naechste(&seiten);
        }
        else if (taste == '-')
        {
            paginierung_vorherige(&seiten);
        }
        else if (taste == 'X')
        {
            return;
        }
    }
}
