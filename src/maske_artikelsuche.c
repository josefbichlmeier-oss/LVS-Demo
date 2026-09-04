#include <stdio.h>

#include "maske_artikelsuche.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "artikel.h"


Ergebnis maske_artikelsuche_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse
)
{
    char zeile[140];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("ARTIKELSUCHE");
    bildschirm_schreiben(3, 3, "NUMMER   BEZEICHNUNG                     MENGE");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = 0; i < artikel_anzahl(); i++)
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

    bildschirm_schreiben(5, 20, "ARTIKELNUMMER:");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();

    if (eingabe_zeile(nummer_out, nummer_out_groesse, 20, 20, 20) == -1)
    {
        return ERG_ZURUECK;
    }

    return ERG_OK;
}
