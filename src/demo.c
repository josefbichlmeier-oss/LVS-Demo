#include "artikel.h"
#include "kunde.h"
#include "auftragsverwaltung.h"
#include "lagerbewegungsbestand.h"


void demo_daten_initialisieren(void)
{
    Auftrag *auftrag;

    artikelbestand_initialisieren();
    kundenbestand_initialisieren();
    auftragsverwaltung_initialisieren();
    lagerbewegungsbestand_initialisieren();

    /* Ein Beispielauftrag "in Bearbeitung" (Positionen erfasst,
     * aber noch nicht ausgeliefert) */
    auftrag = auftrag_neu("1001");
    if (auftrag)
    {
        auftrag_position_hinzufuegen(auftrag, "1001", 50);
        auftrag_position_hinzufuegen(auftrag, "1002", 50);
    }

    /* Ein zweiter, noch offener Beispielauftrag */
    auftrag = auftrag_neu("1000");
    if (auftrag)
    {
        auftrag_position_hinzufuegen(auftrag, "1003", 100);
    }
}
