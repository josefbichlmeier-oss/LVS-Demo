#include <stdio.h>

#include "maske_kundenuebersicht.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "kunde.h"


Ergebnis maske_kundenuebersicht_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse
)
{
    char zeile[140];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("KUNDENAUSWAHL");
    bildschirm_schreiben(2, 3, "NR       NAME");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = 0; i < kunden_anzahl(); i++)
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

    bildschirm_schreiben(5, 22, "KUNDENNUMMER:");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();

    if (eingabe_zeile(nummer_out, nummer_out_groesse, 20, 20, 22) == -1)
    {
        return ERG_ZURUECK;
    }

    return ERG_OK;
}
