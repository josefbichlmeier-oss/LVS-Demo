#ifndef D621_MASKE_WARENAUSGANG_H
#define D621_MASKE_WARENAUSGANG_H

#include <stddef.h>
#include "ergebnis.h"

Ergebnis maske_warenausgang_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse,
    int *menge_out
);

/* ERG_OK / ERG_NICHT_GEFUNDEN / ERG_BESTAND_UNZUREICHEND */
Ergebnis maske_warenausgang_buchen(
    const char *artikelnummer,
    int menge
);

#endif
