#include <stdio.h>

#include "auftragsanzeige.h"
#include "bildschirm.h"
#include "artikel.h"

void auftragsanzeige_ausgeben(
    const Auftrag *auftrag
)
{
    int i;
    char text[80];

    if (auftrag == NULL)
        return;

    bildschirm_loeschen();

    bildschirm_text(30, 2, "D621-LVS");
    bildschirm_text(27, 3, "AUFTRAGSANZEIGE");

    bildschirm_text(0, 5, "AUFTRAG:");

    snprintf(
        text,
        sizeof(text),
        "%d",
        auftrag->nummer
    );
    bildschirm_text(10, 5, text);

    bildschirm_text(45, 5, "STATUS:");
    bildschirm_text(
        53,
        5,
        auftrag_status_text(auftrag->status)
    );

    bildschirm_text(0, 7, "KUNDE:");
    bildschirm_text(10, 7, auftrag->kundennummer);

    bildschirm_text(0, 9, "POSITIONEN:");

    snprintf(
        text,
        sizeof(text),
        "%d",
        auftrag->positionen_anzahl
    );
    bildschirm_text(12, 9, text);

    bildschirm_text(0, 11, "POS");
    bildschirm_text(6, 11, "ARTIKEL");
    bildschirm_text(22, 11, "BEZEICHNUNG");
    bildschirm_text(65, 11, "MENGE");

    for (i = 0; i < auftrag->positionen_anzahl; i++)
    {
        Auftragsposition *position =
            &auftrag->positionen[i];

        Artikel *artikel =
            artikel_finden(position->artikelnummer);

        snprintf(
            text,
            sizeof(text),
            "%02d",
            i + 1
        );
        bildschirm_text(0, 13 + i, text);

        bildschirm_text(
            6,
            13 + i,
            position->artikelnummer
        );

        if (artikel != NULL)
        {
            bildschirm_text(
                22,
                13 + i,
                artikel->bezeichnung
            );
        }

        snprintf(
            text,
            sizeof(text),
            "%d",
            position->menge
        );
        bildschirm_text(67, 13 + i, text);
    }

    bildschirm_text(0, 25, "ESC ZURUECK");

    bildschirm_ausgeben();
}
