#include <ctype.h>

#include "maske_kundenmenue.h"
#include "bildschirm.h"
#include "eingabe.h"


Ergebnis maske_kundenmenue_anzeigen(void)
{
    for (;;)
    {
        bildschirm_loeschen();
        bildschirm_titel("KUNDEN");
        bildschirm_schreiben(5, 3, "1  KUNDENUEBERSICHT");
        bildschirm_aktion("X  ZURUECK  ");
        bildschirm_ausgeben();

        char taste = (char)toupper((unsigned char)eingabe_taste());

        switch (taste)
        {
            case '1': return ERG_ANZEIGEN;
            case 'X': return ERG_ZURUECK;
            default:  break;
        }
    }
}
