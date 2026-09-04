#ifndef D621_MASKE_AUFTRAGSANZEIGE_H
#define D621_MASKE_AUFTRAGSANZEIGE_H

#include "ergebnis.h"
#include "auftrag.h"

/* ERG_AUSLIEFERN oder ERG_ZURUECK */
Ergebnis maske_auftragsanzeige_anzeigen(const Auftrag *auftrag);

#endif
