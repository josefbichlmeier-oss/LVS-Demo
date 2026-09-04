#include <stdio.h>
#include <stdlib.h>

#include "maske_auftragsuebersicht.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "auftragsverwaltung.h"
#include "kunde.h"


Ergebnis maske_auftragsuebersicht_anzeigen(int *nummer_out)
{
    char zeile[140];
    char nummer_puffer[16];
    int y = 5;

    bildschirm_loeschen();
    bildschirm_titel("AUFTRAGSUEBERSICHT");
    bildschirm_schreiben(2, 3, "NR       KUNDE                     STATUS");
    bildschirm_schreiben(2, 4, "------------------------------------------------------------");

    for (int i = 0; i < auftrags_anzahl(); i++)
    {
        Auftrag *auftrag = auftrag_at(i);
        Kunde *kunde = kunde_finden(auftrag->kundennummer);

        const char *kundenname = kunde ? kunde->name : "UNBEKANNT";

        snprintf(
            zeile, sizeof(zeile),
            "%-8d %-25s %-15s",
            auftrag->nummer,
            kundenname,
            auftrag_status_text(auftrag->status)
        );

        bildschirm_feld(2, y, zeile);
        y++;
    }

    bildschirm_schreiben(5, 22, "AUFTRAGSNUMMER: ");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();

    if (eingabe_zeile(nummer_puffer, sizeof(nummer_puffer), 10, 21, 22) == -1)
    {
        return ERG_ZURUECK;
    }

    *nummer_out = atoi(nummer_puffer);

    return ERG_OK;
}
