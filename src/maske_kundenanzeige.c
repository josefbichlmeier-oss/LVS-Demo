#include <stdio.h>

#include "maske_kundenanzeige.h"
#include "bildschirm.h"
#include "eingabe.h"


Ergebnis maske_kundenanzeige_anzeigen(const Kunde *kunde)
{
    char plz_ort[48];

    bildschirm_loeschen();
    bildschirm_titel("KUNDE");

    bildschirm_schreiben(5, 3, "KUNDENNUMMER:");
    bildschirm_schreiben(5, 4, "NAME:");
    bildschirm_schreiben(5, 5, "STRASSE:");
    bildschirm_schreiben(5, 6, "PLZ / ORT:");
    bildschirm_schreiben(5, 7, "TELEFON:");
    bildschirm_schreiben(5, 8, "ANSPRECHPARTNER:");
    bildschirm_aktion("ESC = ZURUECK");

    bildschirm_feld(25, 3, kunde->nummer);
    bildschirm_feld(25, 4, kunde->name);
    bildschirm_feld(25, 5, kunde->strasse);

    snprintf(plz_ort, sizeof(plz_ort), "%s %s", kunde->plz, kunde->ort);
    bildschirm_feld(25, 6, plz_ort);

    bildschirm_feld(25, 7, kunde->telefon);
    bildschirm_feld(25, 8, kunde->ansprechpartner);

    bildschirm_ausgeben();

    for (;;)
    {
        bildschirm_cursor(26, 26);

        char taste = eingabe_taste();

        if (taste == '\033')
        {
            return ERG_ZURUECK;
        }
    }
}
