#include <stddef.h>

#include "lagerbewegungsbestand.h"
#include "artikel.h"

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


int lagerbewegung_buchen(
    const char *artikelnummer,
    int menge,
    Lagerbewegungstyp typ
)
{
    Artikel *artikel;

    artikel = artikel_finden(artikelnummer);

    if (artikel == NULL)
    {
        return -1;
    }

    if (menge <= 0)
    {
        return -2;
    }

    if (typ == LAGER_AUSGANG)
    {
        if (artikel->bestand < menge)
        {
            return -3;
        }

        artikel->bestand -= menge;
    }
    else
    {
        artikel->bestand += menge;
    }

    return lagerbewegung_hinzufuegen(
        artikelnummer,
        menge,
        typ
    );
}
