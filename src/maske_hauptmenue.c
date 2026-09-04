#include <ctype.h>

#include "maske_hauptmenue.h"
#include "bildschirm.h"
#include "eingabe.h"


Ergebnis maske_hauptmenue_anzeigen(void)
{
    for (;;)
    {
        bildschirm_loeschen();
        bildschirm_titel("HAUPTMENUE");
        bildschirm_schreiben(5, 3, "1  LAGER- UND MATERIALVERWALTUNG");
        bildschirm_schreiben(5, 4, "2  AUFTRAGSVERWALTUNG");
        bildschirm_schreiben(5, 5, "3  ARTIKELSTAMM");
        bildschirm_schreiben(5, 6, "4  KUNDENSTAMM");
        bildschirm_aktion("X  ABMELDEN  ");
        bildschirm_ausgeben();

        char taste = (char)toupper((unsigned char)eingabe_taste());

        switch (taste)
        {
            case '1': return ERG_LAGER;
            case '2': return ERG_AUFTRAG;
            case '3': return ERG_ARTIKEL;
            case '4': return ERG_KUNDE;
            case 'X': return ERG_ENDE;
            default:  break;
        }
    }
}
