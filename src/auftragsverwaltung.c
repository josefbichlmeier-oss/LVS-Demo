#include <stddef.h>

#include "auftragsverwaltung.h"


static Auftrag auftraege[MAX_AUFTRAEGE];

static int auftrags_anzahl_wert = 0;

static int naechste_auftragsnummer =
    ERSTE_AUFTRAGSNUMMER;


void auftragsverwaltung_initialisieren(void)
{
    auftrags_anzahl_wert = 0;

    naechste_auftragsnummer =
        ERSTE_AUFTRAGSNUMMER;
}


Auftrag *auftrag_neu(
    const char *kundennummer
)
{
    if (
        auftrags_anzahl_wert
        >= MAX_AUFTRAEGE
    )
    {
        return NULL;
    }


    Auftrag *auftrag =
        &auftraege[auftrags_anzahl_wert];


    auftrag_initialisieren(
        auftrag,
        naechste_auftragsnummer,
        kundennummer
    );


    naechste_auftragsnummer++;
    auftrags_anzahl_wert++;


    return auftrag;
}


Auftrag *auftrag_finden(
    int nummer
)
{
    for (
        int i = 0;
        i < auftrags_anzahl_wert;
        i++
    )
    {
        if (
            auftraege[i].nummer
            == nummer
        )
        {
            return &auftraege[i];
        }
    }


    return NULL;
}


int auftrags_anzahl(void)
{
    return auftrags_anzahl_wert;
}


Auftrag *auftrag_at(
    int index
)
{
    if (
        index < 0 ||
        index >= auftrags_anzahl_wert
    )
    {
        return NULL;
    }


    return &auftraege[index];
}
