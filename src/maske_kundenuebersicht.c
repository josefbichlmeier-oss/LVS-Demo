#include <stdio.h>

#include "maske_kundenuebersicht.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "kunde.h"
#include "paginierung.h"

#define ZEILEN_PRO_SEITE 14


static void liste_zeichnen(const Paginierung *seiten)
{
    char zeile[140];
    char hinweis[40];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("KUNDENAUSWAHL");
    bildschirm_schreiben(2, 3, "NR       NAME");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = paginierung_start_index(seiten); i < paginierung_ende_index(seiten); i++)
    {
        Kunde *kunde = kunde_at(i);

        snprintf(
            zeile, sizeof(zeile),
            "%-8s %-30s",
            kunde->nummer,
            kunde->name
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    paginierung_hinweis(hinweis, sizeof(hinweis), seiten);
    bildschirm_schreiben(2, 20, hinweis);

    bildschirm_schreiben(5, 22, "KUNDENNUMMER:");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();
}


Ergebnis maske_kundenuebersicht_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse
)
{
    Paginierung seiten = { 0, ZEILEN_PRO_SEITE, kunden_anzahl() };

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
                erste_taste, nummer_out, nummer_out_groesse, 20, 20, 22) == -1)
        {
            return ERG_ZURUECK;
        }

        return ERG_OK;
    }
}
