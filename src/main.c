#include <stdio.h>

#include "artikel.h"
#include "kunde.h"
#include "auftrag.h"
#include "auftragsverwaltung.h"
#include "demo.h"


int main(void)
{
    demo_daten_initialisieren();


    Kunde *kunde =
        kunde_finden("1001");

    if (kunde == NULL)
    {
        printf("KUNDE NICHT GEFUNDEN\n");
        return 1;
    }


    Auftrag *auftrag =
        auftrag_neu(kunde->nummer);

    if (auftrag == NULL)
    {
        printf("AUFTRAG KANN NICHT ANGELEGT WERDEN\n");
        return 1;
    }


    auftrag_position_hinzufuegen(
        auftrag,
        "1001",
        20
    );


    printf(
        "AUFTRAG %d\n",
        auftrag->nummer
    );

    printf(
        "KUNDE %s %s\n",
        kunde->nummer,
        kunde->name
    );

    printf(
        "STATUS %d\n",
        auftrag->status
    );

    printf(
        "POSITIONEN %d\n",
        auftrag->positionen_anzahl
    );


    return 0;
}
