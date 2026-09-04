#ifndef D621_MASKE_WARENEINGANG_H
#define D621_MASKE_WARENEINGANG_H

#include <stddef.h>
#include "ergebnis.h"

/* Erfasst Artikelnummer + Menge fuer einen Wareneingang.
 * ERG_OK      -> nummer_out/menge_out gefuellt
 * ERG_ZURUECK -> ESC gedrueckt */
Ergebnis maske_wareneingang_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse,
    int *menge_out
);

/* Bucht den erfassten Wareneingang.
 * ERG_OK               -> gebucht
 * ERG_NICHT_GEFUNDEN    -> Artikel unbekannt */
Ergebnis maske_wareneingang_buchen(
    const char *artikelnummer,
    int menge
);

#endif
