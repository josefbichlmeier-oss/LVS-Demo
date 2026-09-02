#include <stdio.h>

#include "lagerbewegungsbestand.h"

int main(void)
{
    Lagerbewegung *bewegung;

    lagerbewegungsbestand_initialisieren();

    lagerbewegung_hinzufuegen(
        "1001",
        10,
        LAGER_EINGANG
    );

    lagerbewegung_hinzufuegen(
        "1001",
        3,
        LAGER_AUSGANG
    );

    printf("Anzahl Bewegungen: %d\n",
           lagerbewegungs_anzahl());

    for (int i = 0; i < lagerbewegungs_anzahl(); i++)
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
