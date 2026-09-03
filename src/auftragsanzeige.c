#include <stdio.h>

#include "auftragsanzeige.h"
#include "artikel.h"
#include "kunde.h"

#define BILDSCHIRMBREITE 74
#define MAX_ZEILE 26

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

    printf("\n");
    printf("                         AUFTRAGSANZEIGE\n");
    printf("--------------------------------------------------------------------------\n");

    printf(
        "AUFTRAG: %04d                                      STATUS: %-12s\n",
        auftrag->nummer,
        auftrag_status_text(auftrag->status)
    );

    kunde = kunde_finden(auftrag->kundennummer);

    if (kunde != NULL)
    {
        printf(
            "KUNDE:   %-16s \n         %-47s\n",
            kunde->nummer,
            kunde->name
        );
    }
    else
    {
        printf(
            "KUNDE:   %-16s %-47s\n",
            auftrag->kundennummer,
            "UNBEKANNT"
        );
    }

    printf(
        "\nPOSITIONEN: %-2d\n",
        auftrag->positionen_anzahl
    );

    printf("\n");

    printf(
        "POS  ARTIKEL        BEZEICHNUNG                              MENGE\n"
    );

    printf(
        "------------------------------------------------------------------------\n"
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
     * Restliche Zeilen bis zur festen Bildschirmhöhe.
     */

    for (i = auftrag->positionen_anzahl; i < 10; i++)
    {
        printf("\n");
    }

    printf("\n");

    printf(
        "[ESC] ZURUECK\n"
    );

    printf(
        "\n"
    );
}
