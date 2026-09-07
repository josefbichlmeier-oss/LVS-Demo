#include <stdio.h>
#include <stdlib.h>

#include "maske_datumzeit.h"
#include "bildschirm.h"
#include "eingabe.h"
#include "systemzeit.h"
#include "maske_fehlermeldung.h"
#include "maske_meldung.h"


/* Schaltjahrpruefung fuer die Tagesbereichs-Validierung */
static int ist_schaltjahr(int jahr)
{
    return (jahr % 4 == 0 && jahr % 100 != 0) || (jahr % 400 == 0);
}


static int tage_im_monat(int monat, int jahr)
{
    static const int tage[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (monat < 1 || monat > 12)
    {
        return 0;
    }

    if (monat == 2 && ist_schaltjahr(jahr))
    {
        return 29;
    }

    return tage[monat - 1];
}


void maske_datumzeit_anzeigen(void)
{
    for (;;)
    {
        char tag_puffer[4];
        char monat_puffer[4];
        char jahr_puffer[6];
        char stunde_puffer[4];
        char minute_puffer[4];
        char aktuell[24];

        bildschirm_loeschen();
        bildschirm_titel("DATUM / UHRZEIT EINSTELLEN");

        if (systemzeit_ist_gesetzt())
        {
            systemzeit_text(aktuell, sizeof(aktuell));
        }
        else
        {
            snprintf(aktuell, sizeof(aktuell), "NICHT GESETZT");
        }

        bildschirm_schreiben(2, 3, "AKTUELL EINGESTELLT:");
        bildschirm_feld(24, 3, aktuell);

        bildschirm_schreiben(2, 6,  "TAG     (TT)  :");
        bildschirm_schreiben(2, 7,  "MONAT   (MM)  :");
        bildschirm_schreiben(2, 8,  "JAHR    (JJJJ):");
        bildschirm_schreiben(2, 9,  "STUNDE  (HH)  :");
        bildschirm_schreiben(2, 10, "MINUTE  (MM)  :");
        bildschirm_aktion("ESC = ZURUECK");
        bildschirm_ausgeben();

        if (eingabe_zeile(tag_puffer, sizeof(tag_puffer), 2, 20, 6) == -1)
        {
            return;
        }

        if (eingabe_zeile(monat_puffer, sizeof(monat_puffer), 2, 20, 7) == -1)
        {
            return;
        }

        if (eingabe_zeile(jahr_puffer, sizeof(jahr_puffer), 4, 20, 8) == -1)
        {
            return;
        }

        if (eingabe_zeile(stunde_puffer, sizeof(stunde_puffer), 2, 20, 9) == -1)
        {
            return;
        }

        if (eingabe_zeile(minute_puffer, sizeof(minute_puffer), 2, 20, 10) == -1)
        {
            return;
        }

        int tag = atoi(tag_puffer);
        int monat = atoi(monat_puffer);
        int jahr = atoi(jahr_puffer);
        int stunde = atoi(stunde_puffer);
        int minute = atoi(minute_puffer);

        if (jahr < 2000 || jahr > 2099 ||
            monat < 1 || monat > 12 ||
            tag < 1 || tag > tage_im_monat(monat, jahr) ||
            stunde < 0 || stunde > 23 ||
            minute < 0 || minute > 59)
        {
            maske_fehlermeldung_anzeigen("UNGUELTIGES DATUM/UHRZEIT");
            continue;
        }

        systemzeit_setzen(tag, monat, jahr, stunde, minute);

        maske_meldung_anzeigen("UHRZEIT EINGESTELLT");

        return;
    }
}
