#include <string.h>

#include "auftrag.h"
#include "artikel.h"


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

    auftrag->status = AUFTRAG_NEU;

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


int auftrag_bestand_abbuchen(
    Auftrag *auftrag
)
{
    for (
        int i = 0;
        i < auftrag->positionen_anzahl;
        i++
    )
    {
        Auftragsposition *position =
            &auftrag->positionen[i];


        Artikel *artikel =
            artikel_finden(
                position->artikelnummer
            );


        if (artikel == NULL)
        {
            return -1;
        }


        if (
            artikel->bestand
            < position->menge
        )
        {
            return -2;
        }
    }


    /*
     * Erst wenn alle Positionen
     * geprüft wurden, buchen wir ab.
     */

    for (
        int i = 0;
        i < auftrag->positionen_anzahl;
        i++
    )
    {
        Auftragsposition *position =
            &auftrag->positionen[i];


        Artikel *artikel =
            artikel_finden(
                position->artikelnummer
            );


        artikel->bestand -=
            position->menge;
    }


    return 0;
}
