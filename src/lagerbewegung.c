#include <string.h>

#include "lagerbewegung.h"


Lagerbewegung lagerbewegung_erstellen(
    const char *artikelnummer,
    int menge,
    Lagerbewegungstyp typ
)
{
    Lagerbewegung bewegung;


    strncpy(
        bewegung.artikelnummer,
        artikelnummer,
        sizeof(bewegung.artikelnummer) - 1
    );

    bewegung.artikelnummer[
        sizeof(bewegung.artikelnummer) - 1
    ] = '\0';


    bewegung.menge = menge;
    bewegung.typ = typ;


    return bewegung;
}
