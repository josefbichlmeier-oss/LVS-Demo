/*
 * D621-LVS
 *
 * Manuell einstellbare Systemzeit - Ersatz fuer eine fehlende
 * Echtzeituhr, vor allem auf dem ESP32 gedacht (der Linux-Build
 * zeigt ohne manuelle Einstellung weiterhin die echte Systemzeit,
 * siehe zeit_port.h). Einmal gesetzt, laeuft die Uhrzeit anhand
 * einer monotonen Systemuhr (monotonzeit.h) in Echtzeit weiter -
 * unabhaengig davon, ob/wie oft der Bildschirm neu gezeichnet wird.
 */

#ifndef D621_SYSTEMZEIT_H
#define D621_SYSTEMZEIT_H

#include <stddef.h>

/* Setzt Datum und Uhrzeit. jahr vierstellig (z.B. 2026), monat
 * 1-12, tag 1-31 (kalendarisch gueltig fuer den jeweiligen Monat),
 * stunde 0-23, minute 0-59. Keine Validierung hier - Aufrufer
 * (maske_datumzeit.c) prueft die Eingabe vorher. */
void systemzeit_setzen(
    int tag,
    int monat,
    int jahr,
    int stunde,
    int minute
);

/* 1, wenn systemzeit_setzen() bereits aufgerufen wurde, sonst 0. */
int systemzeit_ist_gesetzt(void);

/* Schreibt die aktuelle (weitergezaehlte) Systemzeit im Format
 * "TT.MM.JJJJ HH:MM" nach puffer. Nur sinnvoll, wenn
 * systemzeit_ist_gesetzt() wahr ist. */
void systemzeit_text(char *puffer, size_t groesse);

#endif
