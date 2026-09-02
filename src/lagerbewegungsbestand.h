#ifndef D621_LAGERBEWEGUNGSBESTAND_H
#define D621_LAGERBEWEGUNGSBESTAND_H

#include "lagerbewegung.h"

#define MAX_LAGERBEWEGUNGEN 200

void lagerbewegungsbestand_initialisieren(void);

int lagerbewegung_hinzufuegen(
    const char *artikelnummer,
    int menge,
    Lagerbewegungstyp typ
);

int lagerbewegungs_anzahl(void);

Lagerbewegung *lagerbewegung_at(
    int index
);

int lagerbewegung_buchen(
    const char *artikelnummer,
    int menge,
    Lagerbewegungstyp typ
);

#endif
