#include <stdio.h>

#include "artikel.h"
#include "lagerbewegungsbestand.h"

int main(void)
{
    Artikel *artikel;

    artikelbestand_initialisieren();
    lagerbewegungsbestand_initialisieren();

    artikel = artikel_finden("1001");

    printf("Anfangsbestand: %d\n", artikel->bestand);

    printf(
        "Eingang buchen: %d\n",
        lagerbewegung_buchen(
            "1001",
            10,
            LAGER_EINGANG
        )
    );

    printf("Bestand nach Eingang: %d\n", artikel->bestand);

    printf(
        "Ausgang buchen: %d\n",
        lagerbewegung_buchen(
            "1001",
            3,
            LAGER_AUSGANG
        )
    );

    printf("Bestand nach Ausgang: %d\n", artikel->bestand);

    printf(
        "Unbekannter Artikel: %d\n",
        lagerbewegung_buchen(
            "9999",
            5,
            LAGER_AUSGANG
        )
    );

    printf(
        "Zu grosser Ausgang: %d\n",
        lagerbewegung_buchen(
            "1001",
            999999,
            LAGER_AUSGANG
        )
    );

    printf(
        "Anzahl Lagerbewegungen: %d\n",
        lagerbewegungs_anzahl()
    );

    printf("Bestand nach Fehlbuchung: %d\n", artikel->bestand);

    return 0;
}
