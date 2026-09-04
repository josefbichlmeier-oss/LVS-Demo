/*
 * D621-LVS
 *
 * Liefert einen kurzen Zeittext fuer die Kopfzeile (siehe
 * bildschirm_titel()). Unter Linux die echte Systemzeit
 * (entspricht Ruby Bildschirm#zeit -> Time.now.strftime), auf dem
 * ESP32 mangels eingebauter Echtzeituhr die Laufzeit seit dem
 * letzten Start (kann spaeter leicht durch NTP oder ein externes
 * RTC-Modul wie das DS3231 ersetzt werden).
 */

#ifndef D621_ZEIT_PORT_H
#define D621_ZEIT_PORT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void zeit_text(char *puffer, size_t groesse);

#ifdef __cplusplus
}
#endif

#endif
