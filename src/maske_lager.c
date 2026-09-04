#include <ctype.h>

#include "maske_lager.h"
#include "bildschirm.h"
#include "eingabe.h"


Ergebnis maske_lager_anzeigen(void)
{
    for (;;)
    {
        bildschirm_loeschen();
        bildschirm_titel("LAGER");
        bildschirm_schreiben(5, 3, "1  BESTAND ANZEIGEN");
        bildschirm_schreiben(5, 4, "2  ARTIKEL SUCHEN");
        bildschirm_schreiben(5, 5, "3  WARENEINGANG");
        bildschirm_schreiben(5, 6, "4  WARENAUSGANG");
        bildschirm_schreiben(5, 7, "5  LAGERBEWEGUNGEN");
        bildschirm_aktion("X  ZURUECK  ");
        bildschirm_ausgeben();

        char taste = (char)toupper((unsigned char)eingabe_taste());

        switch (taste)
        {
            case '1': return ERG_BESTAND;
            case '2': return ERG_SUCHE;
            case '3': return ERG_WARENEINGANG;
            case '4': return ERG_WARENAUSGANG;
            case '5': return ERG_BEWEGUNGEN;
            case 'X': return ERG_ZURUECK;
            default:  break;
        }
    }
}
