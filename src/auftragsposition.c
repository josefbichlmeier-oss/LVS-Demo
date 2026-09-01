#include <string.h>

#include "auftragsposition.h"


Auftragsposition auftragsposition_erstellen(
    const char *artikelnummer,
    int menge
)
{
    Auftragsposition position;

    strncpy(
        position.artikelnummer,
        artikelnummer,
        sizeof(position.artikelnummer) - 1
    );

    position.artikelnummer[
        sizeof(position.artikelnummer) - 1
    ] = '\0';

    position.menge = menge;

    return position;
}
