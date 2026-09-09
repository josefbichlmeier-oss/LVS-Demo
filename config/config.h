/*
 * D621-LVS
 *
 * Zentrale Konfiguration
 *
 * Gilt fuer beide Zielplattformen (Linux-Debug und ESP32/Hazeltine).
 */

#ifndef D621_CONFIG_H
#define D621_CONFIG_H

/* Bildschirmgeometrie (identisch zum Hazeltine 2000A/B und zur Ruby-Vorlage) */
#define D621_BREITE 74
#define D621_HOEHE  27

/* Serielle Parameter zum angeschlossenen Terminal (9600 8N1) -
 * gilt fuer Hazeltine wie VT220 gleichermassen, siehe
 * D621_ESP32_TERMINAL unten. Ein VT220 kann in der Praxis auch
 * hoehere Baudraten (19200, 38400) - Wert bei Bedarf anpassen,
 * je nachdem, was die tatsaechliche Verkabelung/das Terminal
 * zulaesst. */
#define D621_BAUDRATE 9600

/* Linux-Debug: Geraetedatei, falls die Hazeltine-Bytefolge testweise
 * ueber eine echte serielle Schnittstelle am PC ausgegeben werden soll.
 * Fuer den normalen Debug-Betrieb (ANSI auf der virtuellen Konsole)
 * wird dieser Wert nicht benoetigt. */
#define D621_SERIELLE_SCHNITTSTELLE "/dev/ttyUSB0"

/* ESP32: Hardware-UART und Pins fuer die Verbindung zum
 * angeschlossenen seriellen Terminal (ueber einen RS232-
 * Pegelwandler wie den MAX3232). Es wird UART2 verwendet, damit
 * UART0 frei fuer USB/Programmierung/Debug-Log bleibt (siehe
 * D621_DEBUG_LOG_AKTIV weiter unten). Gilt fuer Hazeltine UND
 * VT220 gleichermassen - beide sind alternative, sich
 * gegenseitig ausschliessende Bauziele derselben Hardware-Anbindung
 * (siehe D621_ESP32_TERMINAL). */
#define D621_ESP32_UART_NUM   2
#define D621_ESP32_RXD_PIN    16
#define D621_ESP32_TXD_PIN    17

/*
 * Welches serielle Terminal am ESP32 angeschlossen ist. Betrifft
 * nur PLATFORM_ESP32 - der Linux-Debug-Build nutzt immer
 * terminal_linux.c (ANSI-Escapecodes auf der virtuellen Konsole)
 * und ist von dieser Einstellung unberuehrt.
 *
 *   D621_TERMINAL_HAZELTINE  Hazeltine 2000A/B (terminal_hazeltine.c)
 *   D621_TERMINAL_VT220      DEC VT220 (terminal_vt220.c)
 *
 * Beide Terminaltreiber sind immer Teil des Quellbaums - welcher
 * davon tatsaechlich Code erzeugt, entscheidet allein dieser
 * Schalter (siehe #if in terminal_hazeltine.c/terminal_vt220.c).
 * Kein gleichzeitiger Betrieb beider Terminals an einem ESP32 -
 * fuer zwei Terminals gleichzeitig waere eine zweite UART-Instanz
 * (UART1) und ein zweiter Satz Terminal-/Bildschirm-Funktionen
 * noetig, was hier bewusst nicht umgesetzt ist.
 */
#define D621_TERMINAL_HAZELTINE 1
#define D621_TERMINAL_VT220     2

#define D621_ESP32_TERMINAL D621_TERMINAL_HAZELTINE

/* Die Tastatur des angeschlossenen Terminals sendet ihre
 * Tastendruecke unabhaengig vom Terminaltyp ueber dieselbe
 * UART-Leitung zurueck (siehe src/tastatur_seriell.c) - daher
 * keine separate Konfiguration je Terminaltyp noetig. */

/* Maximale Anzahl gleichzeitig gemerkter Bildschirmaenderungen
 * (Dirty-Tracking, siehe bildschirm.c) */
#define D621_MAX_AENDERUNGEN 256

/*
 * Optionales Nokia 5110 (PCD8544) Diagnose-Display, ESP32-only.
 *
 * Rein fuer Debugging/Betriebskontrolle vor Ort gedacht - zeigt
 * Laufzeit, freien Heap-Speicher sowie gesendete/empfangene
 * UART-Bytes und die zuletzt vom Hazeltine empfangene Taste (Hex).
 * Voellig unabhaengig von der Hazeltine-Anbindung, betrifft NICHT
 * die eigentliche Anwendungslogik.
 *
 * Auf 0 setzen, wenn kein Display angeschlossen ist - dann wird
 * weder die Adafruit-Bibliothek eingebunden noch irgendein Pin
 * dafuer beansprucht (siehe src/diagnose_anzeige.cpp).
 *
 * Benoetigt (nur wenn aktiv) die PlatformIO-Bibliotheken
 * "Adafruit GFX Library" und "Adafruit PCD8544 Nokia 5110 LCD
 * library" (siehe platformio.ini lib_deps).
 */
#define D621_NOKIA5110_AKTIV 0

/* Pins fuer das Nokia 5110 - per Software-SPI (bit-banging), daher
 * beliebige freie GPIOs moeglich, muessen nur von UART2
 * (RXD/TXD oben) verschieden sein. Vorbelegung passt auf die
 * meisten gaengigen ESP32-Devkits. */
#define D621_ESP32_NOKIA_CLK_PIN  18
#define D621_ESP32_NOKIA_DIN_PIN  23
#define D621_ESP32_NOKIA_DC_PIN    4
#define D621_ESP32_NOKIA_CS_PIN    5
#define D621_ESP32_NOKIA_RST_PIN   2

/*
 * Debug-Logging ueber die serielle USB/Programmierschnittstelle
 * des ESP32 (UART0/Serial) - unabhaengig von UART2, das fuer die
 * Hazeltine-Verbindung reserviert ist. Praktisch mit einem
 * simplen "pio device monitor" oder jedem seriellen Terminal am
 * USB-Anschluss zu verfolgen, auch ohne Nokia-5110-Display.
 *
 * Unter Linux (Debug-Build) landet dieselbe Ausgabe auf stderr.
 *
 * Auf 0 setzen, um jegliches Debug-Logging abzuschalten.
 */
#define D621_DEBUG_LOG_AKTIV 0
#define D621_DEBUG_BAUDRATE  115200

#endif
