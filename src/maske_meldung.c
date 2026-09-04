#include "maske_meldung.h"
#include "bildschirm.h"
#include "eingabe.h"


void maske_meldung_anzeigen(const char *text)
{
    bildschirm_loeschen();
    bildschirm_titel("MELDUNG");
    bildschirm_status("", text);
    bildschirm_aktion("CR = WEITER");
    bildschirm_ausgeben();

    for (;;)
    {
        char taste = eingabe_taste();

        if (taste == '\r' || taste == '\n')
        {
            return;
        }
    }
}
