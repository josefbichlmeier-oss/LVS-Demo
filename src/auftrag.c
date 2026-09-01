#include <string.h>

#include "auftrag.h"


void auftrag_initialisieren(
    Auftrag *auftrag,
    int nummer,
    const char *kundennummer
)
{
    auftrag->nummer = nummer;

    strncpy(
        auftrag->kundennummer,
        kundennummer,
        sizeof(auftrag->kundennummer) - 1
    );

    auftrag->kundennummer[
        sizeof(auftrag->kundennummer) - 1
    ] = '\0';


    strncpy(
        auftrag->status,
        "NEU",
        sizeof(auftrag->status) - 1
    );

    auftrag->status[
        sizeof(auftrag->status) - 1
    ] = '\0';


    auftrag->positionen_anzahl = 0;
}


int auftrag_position_hinzufuegen(
    Auftrag *auftrag,
    const char *artikelnummer,
    int menge
)
{
    if (
        auftrag->positionen_anzahl
        >= MAX_POSITIONEN
    )
    {
        return -1;
    }


    Auftragsposition *position =
        &auftrag->positionen[
            auftrag->positionen_anzahl
        ];


    *position =
        auftragsposition_erstellen(
            artikelnummer,
            menge
        );


    auftrag->positionen_anzahl++;

    return 0;
}
