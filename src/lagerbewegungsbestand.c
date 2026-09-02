#include <stddef.h>

#include "lagerbewegungsbestand.h"

static Lagerbewegung bewegungen[MAX_LAGERBEWEGUNGEN];

static int anzahl = 0;

void lagerbewegungsbestand_initialisieren(void)
{
    anzahl = 0;
}

int lagerbewegung_hinzufuegen(
    const char *artikelnummer,
    int menge,
    Lagerbewegungstyp typ
)
{
    if (anzahl >= MAX_LAGERBEWEGUNGEN)
    {
        return -1;
    }

    bewegungen[anzahl] =
        lagerbewegung_erstellen(
            artikelnummer,
            menge,
            typ
        );

    anzahl++;

    return 0;
}

int lagerbewegungs_anzahl(void)
{
    return anzahl;
}

Lagerbewegung *lagerbewegung_at(int index)
{
    if (index < 0 || index >= anzahl)
    {
        return NULL;
    }

    return &bewegungen[index];
}
