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
     * Auftrag darf nur einmal abgewickelt werden.
     */
    if (auftrag->status == AUFTRAG_ABGESCHLOSSEN)
    {
        return -5;
    }

    /*
     * Auftrag wird jetzt bearbeitet.
     */
    auftrag->status = AUFTRAG_BEARBEITET;

    /*
     * Zuerst prüfen, ob alle Positionen
     * ausreichend Bestand haben.
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

    /*
     * Auftrag erfolgreich abgeschlossen.
     */
    auftrag->status = AUFTRAG_ABGESCHLOSSEN;

    return 0;
}


const char *auftrag_status_text(
    Auftragsstatus status
)
{
    switch (status)
    {
        case AUFTRAG_NEU:
            return "NEU";

        case AUFTRAG_BEARBEITET:
            return "BEARBEITET";

        case AUFTRAG_ABGESCHLOSSEN:
            return "ABGESCHLOSSEN";

        default:
            return "UNBEKANNT";
    }
}

/* Beispiel
printf(
    "%04d  %-12s  %s\n",
    auftrag->nummer,
    auftrag->kundennummer,
    auftrag_status_text(auftrag->status)
);
*/
