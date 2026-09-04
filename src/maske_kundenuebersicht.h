#ifndef D621_MASKE_KUNDENUEBERSICHT_H
#define D621_MASKE_KUNDENUEBERSICHT_H

#include <stddef.h>
#include "ergebnis.h"

Ergebnis maske_kundenuebersicht_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse
);

#endif
