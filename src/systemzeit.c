#include <stdio.h>

#include "systemzeit.h"
#include "monotonzeit.h"


static int gesetzt = 0;

/* Sekunden des gesetzten Zeitpunkts seit einer festen Epoche
 * (siehe days_from_civil unten), sowie der Wert der monotonen Uhr
 * zum Zeitpunkt des Setzens - die Differenz der monotonen Uhr zu
 * "jetzt" wird bei jeder Abfrage draufaddiert. */
static long basis_sekunden = 0;
static unsigned long monoton_bei_setzen = 0;


/*
 * Tage seit 1970-01-01 fuer ein gregorianisches Kalenderdatum.
 * Bewaehrter, kompakter Algorithmus (Howard Hinnant, public
 * domain), korrekt inkl. Schaltjahren.
 */
static long tage_aus_datum(int jahr, int monat, int tag)
{
    long y = jahr - (monat <= 2 ? 1 : 0);
    long era = (y >= 0 ? y : y - 399) / 400;
    unsigned long yoe = (unsigned long)(y - era * 400);
    unsigned long m = (unsigned long)monat;
    unsigned long doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + (unsigned)tag - 1;
    unsigned long doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;

    return era * 146097 + (long)doe - 719468;
}


/*
 * Umkehrfunktion zu tage_aus_datum().
 */
static void datum_aus_tagen(long tage, int *jahr, int *monat, int *tag)
{
    long z = tage + 719468;
    long era = (z >= 0 ? z : z - 146096) / 146097;
    unsigned long doe = (unsigned long)(z - era * 146097);
    unsigned long yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    long y = (long)yoe + era * 400;
    unsigned long doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    unsigned long mp = (5 * doy + 2) / 153;
    unsigned long d = doy - (153 * mp + 2) / 5 + 1;
    unsigned long m = mp + (mp < 10 ? 3 : -9);

    y += (m <= 2);

    *jahr = (int)y;
    *monat = (int)m;
    *tag = (int)d;
}


void systemzeit_setzen(
    int tag,
    int monat,
    int jahr,
    int stunde,
    int minute
)
{
    long tage = tage_aus_datum(jahr, monat, tag);

    basis_sekunden = tage * 86400L + (long)stunde * 3600L + (long)minute * 60L;
    monoton_bei_setzen = monotonzeit_sekunden();

    gesetzt = 1;
}


int systemzeit_ist_gesetzt(void)
{
    return gesetzt;
}


void systemzeit_text(char *puffer, size_t groesse)
{
    unsigned long vergangen;
    long gesamt_sekunden;
    long tage;
    long rest;
    int jahr, monat, tag, stunde, minute;

    if (!gesetzt)
    {
        puffer[0] = '\0';
        return;
    }

    vergangen = monotonzeit_sekunden() - monoton_bei_setzen;
    gesamt_sekunden = basis_sekunden + (long)vergangen;

    tage = gesamt_sekunden / 86400L;
    rest = gesamt_sekunden % 86400L;

    if (rest < 0)
    {
        rest += 86400L;
        tage -= 1;
    }

    stunde = (int)(rest / 3600L);
    minute = (int)((rest % 3600L) / 60L);

    datum_aus_tagen(tage, &jahr, &monat, &tag);

    snprintf(
        puffer, groesse,
        "%02d.%02d.%04d %02d:%02d",
        tag, monat, jahr, stunde, minute
    );
}
