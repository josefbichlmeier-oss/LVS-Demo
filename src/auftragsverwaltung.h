#ifndef D621_AUFTRAGSVERWALTUNG_H
#define D621_AUFTRAGSVERWALTUNG_H

#include "auftrag.h"

#define MAX_AUFTRAEGE 100
#define ERSTE_AUFTRAGSNUMMER 2600


void auftragsverwaltung_initialisieren(void);

Auftrag *auftrag_neu(
    const char *kundennummer
);

Auftrag *auftrag_finden(
    int nummer
);

int auftrags_anzahl(void);

Auftrag *auftrag_at(
    int index
);

#endif
