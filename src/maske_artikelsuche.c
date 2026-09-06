#include <stdio.h>

#include "maske_artikelsuche.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "artikel.h"
#include "paginierung.h"

#define ZEILEN_PRO_SEITE 13


static void liste_zeichnen(const Paginierung *seiten)
{
    char zeile[140];
    char hinweis[40];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("ARTIKELSUCHE");
    bildschirm_schreiben(3, 3, "NUMMER   BEZEICHNUNG                     MENGE");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = paginierung_start_index(seiten); i < paginierung_ende_index(seiten); i++)
    {
        Artikel *artikel = artikel_at(i);

        snprintf(
            zeile, sizeof(zeile),
            "%-6s %-30s %6d",
            artikel->nummer,
            artikel->bezeichnung,
            artikel->bestand
        );

        bildschirm_feld(5, y, zeile);
        y++;
    }

    paginierung_hinweis(hinweis, sizeof(hinweis), seiten);
    bildschirm_schreiben(5, 18, hinweis);

    bildschirm_schreiben(5, 20, "ARTIKELNUMMER:");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();
}


Ergebnis maske_artikelsuche_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse
)
{
    Paginierung seiten = { 0, ZEILEN_PRO_SEITE, artikel_anzahl() };

    for (;;)
    {
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
                erste_taste, nummer_out, nummer_out_groesse, 20, 20, 20) == -1)
        {
            return ERG_ZURUECK;
        }

        return ERG_OK;
    }
}
