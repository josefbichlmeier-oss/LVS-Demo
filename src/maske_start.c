#include "maske_start.h"
#include "bildschirm.h"
#include "eingabe.h"


Ergebnis maske_start_anzeigen(void)
{
    bildschirm_loeschen();

    bildschirm_titel("DIETZ 621 RECHENANLAGE V1.1");

    bildschirm_schreiben(26,  7, "#       #     #  #####  ");
    bildschirm_schreiben(26,  8, "#       #     # #     # ");
    bildschirm_schreiben(26,  9, "#       #     # #       ");
    bildschirm_schreiben(26, 10, "#       #     #  #####  ");
    bildschirm_schreiben(26, 11, "#        #   #        # ");
    bildschirm_schreiben(26, 12, "#         # #   #     # ");
    bildschirm_schreiben(26, 13, "#######    #     #####  ");
    bildschirm_schreiben(26, 15, "LAGERVERWALTUNGSSYSTEM  ");
    bildschirm_schreiben(26, 17, "COMPUTEUM - VILSHOFEN ");

    bildschirm_aktion("WEITER MIT BELIEBIGE TASTE");

    bildschirm_ausgeben();

    eingabe_warten();

    return ERG_WEITER;
}
