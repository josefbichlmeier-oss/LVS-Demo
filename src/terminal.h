/*
 * D621-LVS
 *
 * Terminal-Schnittstelle.
 *
 * Es gibt genau eine Implementierung pro Zielplattform, ausgewaehlt
 * zur Compile-Zeit (kein Laufzeit-Vtable noetig, da jede Plattform
 * fest an ein Ausgabegeraet gebunden ist):
 *
 *   PLATFORM_LINUX -> terminal_linux.c     ANSI-Escapecodes,
 *                                          lokale virtuelle Konsole
 *                                          (Debug-Betrieb)
 *   PLATFORM_ESP32 -> terminal_hazeltine.c Hazeltine 2000A/B
 *                                          Bytefolgen ueber UART
 *                                          (Zielbetrieb)
 *
 * Beide Implementierungen bieten exakt dieselben Funktionen an.
 */

#ifndef D621_TERMINAL_H
#define D621_TERMINAL_H

void terminal_init(void);

void terminal_loeschen(void);

void terminal_position(int x, int y);

void terminal_hell(void);

void terminal_dunkel(void);

void terminal_schreiben(const char *text);

/* Nicht von der Bildschirmschicht genutzt, aber Teil des
 * Original-Funktionsumfangs (Terminal-Basisklasse/Hazeltine-Treiber
 * in Ruby) und daher aus Vollstaendigkeitsgruenden vorhanden. */
void terminal_cursor_zurueck(void);
void terminal_zeile_loeschen(void);
void terminal_zeichen_loeschen(void);

#endif
