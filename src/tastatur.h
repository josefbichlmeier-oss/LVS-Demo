/*
 * D621-LVS
 *
 * Tastatur-Schnittstelle.
 *
 * PLATFORM_LINUX -> tastatur_linux.c    Raw-Mode-Lesen von stdin
 *                                       (entspricht Ruby
 *                                       LinuxTastatur/STDIN.getch)
 * PLATFORM_ESP32 -> tastatur_seriell.c  Byte-Empfang vom
 *                                       angeschlossenen Terminal
 *                                       (Hazeltine oder VT220,
 *                                       siehe config.h
 *                                       D621_ESP32_TERMINAL) ueber
 *                                       dieselbe UART-Leitung, auf
 *                                       der auch ausgegeben wird
 *                                       (entspricht Ruby
 *                                       HazeltineTastatur)
 */

#ifndef D621_TASTATUR_H
#define D621_TASTATUR_H

void tastatur_init(void);

/* Blockiert, bis ein Zeichen verfuegbar ist, und liefert es zurueck. */
char tastatur_lesen(void);

#endif
