#include <ctype.h>

#include "maske_auftragsmenue.h"
#include "bildschirm.h"
#include "eingabe.h"


Ergebnis maske_auftragsmenue_anzeigen(void)
{
    for (;;)
    {
        bildschirm_loeschen();
        bildschirm_titel("AUFTRAG");
        bildschirm_schreiben(5, 3, "1  AUFTRAGSUEBERSICHT");
        bildschirm_schreiben(5, 4, "2  NEUEN AUFTRAG ERFASSEN");
        bildschirm_aktion("X  ZURUECK  ");
        bildschirm_ausgeben();

        char taste = (char)toupper((unsigned char)eingabe_taste());

        switch (taste)
        {
            case '1': return ERG_ANZEIGEN;
            case '2': return ERG_NEU;
            case 'X': return ERG_ZURUECK;
            default:  break;
        }
    }
}
