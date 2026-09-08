/*
 * D621-LVS
 *
 * Debug-Logging ueber die serielle Programmierschnittstelle des
 * ESP32 (UART0/Serial, USB) - unabhaengig von UART2 (Hazeltine).
 * Unter Linux (Debug-Build) landet dieselbe Ausgabe auf stderr,
 * damit sie sich nicht mit der ANSI-Bildschirmausgabe auf stdout
 * vermischt.
 *
 * Kann in config.h ueber D621_DEBUG_LOG_AKTIV komplett abgeschaltet
 * werden - dann sind beide Funktionen wirkungslose No-Ops.
 */

#ifndef D621_DEBUG_LOG_H
#define D621_DEBUG_LOG_H

void debug_log_init(void);

/*
 * printf-artiges Logging, eine Zeile pro Aufruf (Zeilenumbruch
 * wird automatisch angehaengt - im Formatstring KEIN "\n" angeben).
 * Mit __attribute__((format(printf,...))) markiert, damit GCC/Clang
 * auf dem Linux-Debug-Build Formatstring-Fehler an den Aufrufstellen
 * schon beim Kompilieren meldet.
 */
#if defined(__GNUC__)
void debug_log(const char *format, ...) __attribute__((format(printf, 1, 2)));
#else
void debug_log(const char *format, ...);
#endif

#endif
