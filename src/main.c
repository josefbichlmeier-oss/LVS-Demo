#include <stdio.h>

#include "artikel.h"
#include "auftrag.h"
#include "auftragsverwaltung.h"
#include "lagerbewegungsbestand.h"

int main(void)
{
    Artikel *artikel1;
    Artikel *artikel2;
    Auftrag *auftrag;
    Lagerbewegung *bewegung;

    artikelbestand_initialisieren();
    auftragsverwaltung_initialisieren();
    lagerbewegungsbestand_initialisieren();

    artikel1 = artikel_finden("1001");
    artikel2 = artikel_finden("1002");

    printf("Anfangsbestand 1001: %d\n", artikel1->bestand);
    printf("Anfangsbestand 1002: %d\n", artikel2->bestand);

    auftrag = auftrag_neu("1001");

    auftrag_position_hinzufuegen(
        auftrag,
        "1001",
        3
    );

    auftrag_position_hinzufuegen(
        auftrag,
        "1002",
        5
    );

    printf(
        "Auftrag: %d\n",
        auftrag->nummer
    );

    printf(
        "Positionen: %d\n",
        auftrag->positionen_anzahl
    );

    printf(
        "Abbuchen: %d\n",
        auftrag_bestand_abbuchen(auftrag)
    );

    printf("Bestand 1001: %d\n", artikel1->bestand);
    printf("Bestand 1002: %d\n", artikel2->bestand);

    printf(
        "Lagerbewegungen: %d\n",
        lagerbewegungs_anzahl()
    );

    for (int i = 0;
         i < lagerbewegungs_anzahl();
         i++)
    {
        bewegung = lagerbewegung_at(i);

        printf(
            "%d: Artikel %s, Menge %d, Typ %d\n",
            i,
            bewegung->artikelnummer,
            bewegung->menge,
            bewegung->typ
        );
    }

    return 0;
}
