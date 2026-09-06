#include <ctype.h>
#include <stdio.h>

#include "maske_artikelstamm.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "artikel.h"
#include "paginierung.h"

#define ZEILEN_PRO_SEITE 18


static void liste_zeichnen(const Paginierung *seiten)
{
    char zeile[140];
    char hinweis[40];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("ARTIKELSTAMM");
    bildschirm_schreiben(2, 3, "NUMMER     BEZEICHNUNG");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = paginierung_start_index(seiten); i < paginierung_ende_index(seiten); i++)
    {
        Artikel *artikel = artikel_at(i);

        snprintf(
            zeile, sizeof(zeile),
            "%-10s %-30s",
            artikel->nummer,
            artikel->bezeichnung
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    paginierung_hinweis(hinweis, sizeof(hinweis), seiten);
    bildschirm_schreiben(2, 24, hinweis);

    bildschirm_aktion("X  ZURUECK  ");
    bildschirm_ausgeben();
}


Ergebnis maske_artikelstamm_anzeigen(void)
{
    Paginierung seiten = { 0, ZEILEN_PRO_SEITE, artikel_anzahl() };

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
            return ERG_ZURUECK;
        }
    }
}
