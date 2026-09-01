#ifndef D621_AUFTRAG_H
#define D621_AUFTRAG_H

#include "auftragsposition.h"

#define MAX_POSITIONEN 20

typedef struct
{
    int nummer;
    char kundennummer[16];
    char status[16];

    Auftragsposition positionen[MAX_POSITIONEN];
    int positionen_anzahl;

} Auftrag;


void auftrag_initialisieren(
    Auftrag *auftrag,
    int nummer,
    const char *kundennummer
);


int auftrag_position_hinzufuegen(
    Auftrag *auftrag,
    const char *artikelnummer,
    int menge
);

#endif
