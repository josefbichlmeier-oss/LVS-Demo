#include <stdio.h>

#include "artikel.h"
#include "kunde.h"
#include "auftrag.h"


int main(void)
{
    artikelbestand_initialisieren();
    kundenbestand_initialisieren();


    Kunde *kunde =
        kunde_finden("1001");

    if (kunde == NULL)
    {
        printf("Kunde nicht gefunden\n");
        return 1;
    }


    Auftrag auftrag;

    auftrag_initialisieren(
        &auftrag,
        1,
        kunde->nummer
    );


    auftrag_position_hinzufuegen(
        &auftrag,
        "1001",
        20
    );

    auftrag_position_hinzufuegen(
        &auftrag,
        "1002",
        10
    );


    printf(
        "AUFTRAG %d\n",
        auftrag.nummer
    );

    printf(
        "KUNDE %s %s\n",
        kunde->nummer,
        kunde->name
    );

    printf(
        "STATUS %s\n",
        auftrag.status
    );

    printf(
        "POSITIONEN %d\n\n",
        auftrag.positionen_anzahl
    );


    for (
        int i = 0;
        i < auftrag.positionen_anzahl;
        i++
    )
    {
        Auftragsposition *position =
            &auftrag.positionen[i];

        Artikel *artikel =
            artikel_finden(
                position->artikelnummer
            );

        if (artikel != NULL)
        {
            printf(
                "%s %-20s %d\n",
                artikel->nummer,
                artikel->bezeichnung,
                position->menge
            );
        }
    }


    return 0;
}
