#include <stdio.h>

#include "auftragsanzeige.h"
#include "artikel.h"
#include "kunde.h"

void auftragsanzeige_ausgeben(
    const Auftrag *auftrag
)
{
    int i;
    Artikel *artikel;
    Kunde *kunde;

    if (auftrag == NULL)
    {
        return;
    }

    /*
     * Kopf
     */

    printf("\n");
    printf("                         AUFTRAGSANZEIGE\n");
    printf("\n");

    printf(
        "AUFTRAG: %04d",
        auftrag->nummer
    );

    printf(
        "                              STATUS: %-12s\n",
        auftrag_status_text(auftrag->status)
    );

    /*
     * Kunde
     */

    kunde = kunde_finden(auftrag->kundennummer);

    printf(
        "KUNDE:   %-16s",
        auftrag->kundennummer
    );

    if (kunde != NULL)
    {
        printf("%s", kunde->name);
    }

    printf("\n\n");

    /*
     * Positionen
     */

    printf("POSITIONEN: %d\n\n", auftrag->positionen_anzahl);

    printf(
        "POS  ARTIKEL        BEZEICHNUNG                              MENGE\n"
    );

    printf(
        "------------------------------------------------------------------\n"
    );

    for (i = 0; i < auftrag->positionen_anzahl; i++)
    {
        artikel =
            artikel_finden(
                auftrag->positionen[i].artikelnummer
            );

        if (artikel != NULL)
        {
            printf(
                "%02d   %-14s %-40s %5d\n",
                i + 1,
                artikel->nummer,
                artikel->bezeichnung,
                auftrag->positionen[i].menge
            );
        }
        else
        {
            printf(
                "%02d   %-14s %-40s %5d\n",
                i + 1,
                auftrag->positionen[i].artikelnummer,
                "UNBEKANNT",
                auftrag->positionen[i].menge
            );
        }
    }

    /*
     * Bedienhinweis
     */

    printf("\n\n");
    printf("ESC ZURUECK\n");
}
