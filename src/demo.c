#include "artikel.h"
#include "kunde.h"
#include "auftragsverwaltung.h"


void demo_daten_initialisieren(void)
{
    artikelbestand_initialisieren();
    kundenbestand_initialisieren();
    auftragsverwaltung_initialisieren();
}
