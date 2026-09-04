#include <stdlib.h>

#include "maske_warenausgang.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "lagerbewegungsbestand.h"


Ergebnis maske_warenausgang_anzeigen(
    char *nummer_out,
    size_t nummer_out_groesse,
    int *menge_out
)
{
    char menge_puffer[16];

    bildschirm_loeschen();
    bildschirm_titel("WARENAUSGANG");
    bildschirm_schreiben(5, 3, "ARTIKELNUMMER:");
    bildschirm_schreiben(5, 4, "MENGE:");
    bildschirm_aktion("ESC = ZURUECK");
    bildschirm_ausgeben();

    if (eingabe_zeile(nummer_out, nummer_out_groesse, 10, 20, 3) == -1)
    {
        return ERG_ZURUECK;
    }

    if (eingabe_zeile(menge_puffer, sizeof(menge_puffer), 10, 20, 4) == -1)
    {
        return ERG_ZURUECK;
    }

    *menge_out = atoi(menge_puffer);

    return ERG_OK;
}


Ergebnis maske_warenausgang_buchen(
    const char *artikelnummer,
    int menge
)
{
    int ergebnis =
        lagerbewegung_buchen(artikelnummer, menge, LAGER_AUSGANG);

    if (ergebnis == -1)
    {
        return ERG_NICHT_GEFUNDEN;
    }

    if (ergebnis == -3)
    {
        return ERG_BESTAND_UNZUREICHEND;
    }

    if (ergebnis != 0)
    {
        return ERG_NICHT_GEFUNDEN;
    }

    return ERG_OK;
}
