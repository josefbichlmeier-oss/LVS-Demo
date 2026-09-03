#include <stdio.h>

#include "artikel.h"
#include "kunde.h"
#include "auftrag.h"
#include "auftragsverwaltung.h"
#include "lagerbewegungsbestand.h"
#include "auftragsanzeige.h"

int main(void)
{
    //int i;
    //int j;

    Auftrag *auftrag;

    artikelbestand_initialisieren();
    kundenbestand_initialisieren();
    auftragsverwaltung_initialisieren();
    lagerbewegungsbestand_initialisieren();

    printf("D621-LVS\n");
    printf("========\n\n");

    /*
     * Aufträge anlegen
     */

    auftrag = auftrag_neu("1001");

    auftrag_position_hinzufuegen(
        auftrag,
        "1001",
        5
    );

    auftrag_position_hinzufuegen(
        auftrag,
        "1002",
        3
    );

    auftrag_position_hinzufuegen(
        auftrag,
        "1003",
        17
    );



    auftrag = auftrag_neu("1002");

    auftrag_position_hinzufuegen(
        auftrag,
        "1003",
        10
    );


    auftrag = auftrag_neu("1003");

    auftrag_position_hinzufuegen(
        auftrag,
        "1001",
        2
    );

    auftrag_position_hinzufuegen(
        auftrag,
        "1003",
        4
    );


    /*
     * Auftragsübersicht
     */
/*
    printf("\n");
    printf("AUFTRAGSUEBERSICHT\n");
    printf("------------------\n");

    for (i = 0; i < auftrags_anzahl(); i++)
    {
        auftrag = auftrag_at(i);

        printf(
            "%04d  KUNDE %-4s  %-12s\n",
            auftrag->nummer,
            auftrag->kundennummer,
            auftrag_status_text(auftrag->status)
        );
    }
*/

    /*
     * Auftragsdetails
     */

/*
    printf("\n");
    printf("AUFTRAGSDETAILS\n");
    printf("---------------\n");

    for (i = 0; i < auftrags_anzahl(); i++)
    {
        auftrag = auftrag_at(i);

        printf(
            "\nAuftrag: %04d\n",
            auftrag->nummer
        );

        printf(
            "Kunde:   %s\n",
            auftrag->kundennummer
        );

        printf(
            "Status:  %s\n",
            auftrag_status_text(auftrag->status)
        );

        printf(
            "Positionen: %d\n",
            auftrag->positionen_anzahl
        );

        for (j = 0; j < auftrag->positionen_anzahl; j++)
        {
            printf(
                "  %-10s Menge: %d\n",
                auftrag->positionen[j].artikelnummer,
                auftrag->positionen[j].menge
            );
        }
    }
*/
    
    auftrag = auftrag_finden(2600);

    auftragsanzeige_ausgeben(auftrag);

    return 0;
}
