/*
 * D621-LVS
 *
 * Sekunden seit einem beliebigen, aber festen Referenzpunkt
 * (Programmstart bzw. Systemstart) - laeuft niemals rueckwaerts
 * und ist unabhaengig von einer evtl. gestellten Wanduhr. Dient
 * als Zeitbasis fuer systemzeit.c/h (manuell gesetztes Datum +
 * Uhrzeit, die ab dem Setzen in Echtzeit weiterlaeuft).
 *
 * PLATFORM_LINUX -> monotonzeit_linux.c (CLOCK_MONOTONIC)
 * PLATFORM_ESP32 -> monotonzeit_esp32.cpp (millis())
 */

#ifndef D621_MONOTONZEIT_H
#define D621_MONOTONZEIT_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned long monotonzeit_sekunden(void);

#ifdef __cplusplus
}
#endif

#endif
