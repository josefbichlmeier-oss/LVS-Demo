#include "artikel.h"
#include "kunde.h"
#include "auftragsverwaltung.h"
#include "auftragsanzeige.h"

int main(void)
{
    Auftrag *auftrag;

    artikelbestand_initialisieren();
    kundenbestand_initialisieren();
    auftragsverwaltung_initialisieren();

    auftrag = auftrag_neu("1001");

    auftrag_position_hinzufuegen(
        auftrag,
        "1001",
        5
    );

    auftrag_position_hinzufuegen(
        auftrag,
        "1002",
        3
    );

    auftragsanzeige_ausgeben(auftrag);

    return 0;
}
