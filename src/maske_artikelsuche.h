#ifndef D621_MASKE_ARTIKELSUCHE_H
#define D621_MASKE_ARTIKELSUCHE_H

#include <stddef.h>
#include "ergebnis.h"

/* Zeigt die Artikelliste und liest eine Artikelnummer ein.
 * Rueckgabe ERG_OK  -> nummer_out enthaelt die eingegebene Nummer
 *          ERG_ZURUECK -> ESC gedrueckt */
Ergebnis maske_artikelsuche_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse
);

#endif
