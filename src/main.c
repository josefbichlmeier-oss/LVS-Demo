#include <stdio.h>

#include "artikel.h"
#include "kunde.h"
#include "auftrag.h"
#include "auftragsverwaltung.h"


int main(void)
{
    artikelbestand_initialisieren();
    kundenbestand_initialisieren();
    auftragsverwaltung_initialisieren();


    Auftrag *auftrag1 =
        auftrag_neu("1001");

    Auftrag *auftrag2 =
        auftrag_neu("1002");

    Auftrag *auftrag3 =
        auftrag_neu("1001");


    printf(
        "Auftrag 1: %d / Kunde %s\n",
        auftrag1->nummer,
        auftrag1->kundennummer
    );

    printf(
        "Auftrag 2: %d / Kunde %s\n",
        auftrag2->nummer,
        auftrag2->kundennummer
    );

    printf(
        "Auftrag 3: %d / Kunde %s\n",
        auftrag3->nummer,
        auftrag3->kundennummer
    );


    Auftrag *gesucht =
        auftrag_finden(2601);


    if (gesucht != NULL)
    {
        printf(
            "Gefunden: Auftrag %d\n",
            gesucht->nummer
        );
    }


    printf(
        "Anzahl Auftraege: %d\n",
        auftrags_anzahl()
    );


    printf("###########################################\n");


    Auftrag *auftrag =
        auftrag_neu("1001");


    auftrag_position_hinzufuegen(
        auftrag,
        "1001",
        20
    );


    Artikel *artikel =
        artikel_finden("1001");


    printf(
        "Bestand vorher: %d\n",
        artikel->bestand
    );


    int ergebnis =
        auftrag_bestand_abbuchen(
            auftrag
        );


    printf(
        "Ergebnis: %d\n",
        ergebnis
    );


    printf(
        "Bestand nachher: %d\n",
        artikel->bestand
    );
    
    printf(
        "Status: %d\n",
        auftrag->status
    );
    
    //auftrag->status = AUFTRAG_BEARBEITET;
    if (auftrag_bestand_abbuchen(auftrag) == 0)
    {
        auftrag->status = AUFTRAG_ABGESCHLOSSEN;
    }    

    printf(
        "Status: %d\n",
        auftrag->status
    );
    
    

    return 0;
}
