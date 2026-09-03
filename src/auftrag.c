#include <string.h>

#include "auftrag.h"
#include "artikel.h"
#include "lagerbewegungsbestand.h"


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
    int i;
    Auftragsposition *position;

    if (auftrag == NULL)
    {
        return -4;
    }

    /*
     * Zuerst prüfen, ob alle Positionen
     * ausreichend Bestand haben.
     *
     * Noch keine Buchung durchführen!
     */
    for (i = 0; i < auftrag->positionen_anzahl; i++)
    {
        position = &auftrag->positionen[i];

        Artikel *artikel =
            artikel_finden(position->artikelnummer);

        if (artikel == NULL)
        {
            return -1;
        }

        if (artikel->bestand < position->menge)
        {
            return -2;
        }
    }

    /*
     * Jetzt alle Positionen als
     * Lagerausgang buchen.
     */
    for (i = 0; i < auftrag->positionen_anzahl; i++)
    {
        position = &auftrag->positionen[i];

        if (lagerbewegung_buchen(
                position->artikelnummer,
                position->menge,
                LAGER_AUSGANG) != 0)
        {
            return -3;
        }
    }

    return 0;
}
