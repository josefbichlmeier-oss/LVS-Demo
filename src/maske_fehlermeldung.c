#include "maske_fehlermeldung.h"
#include "bildschirm.h"
#include "eingabe.h"


void maske_fehlermeldung_anzeigen(const char *text)
{
    bildschirm_status(text, "FEHLER");
    bildschirm_ausgeben();

    eingabe_warten();

    bildschirm_status("", "BEREIT");
    bildschirm_ausgeben();
}
