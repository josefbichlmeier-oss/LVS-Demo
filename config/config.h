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

/* Serielle Parameter zum Hazeltine-Terminal (9600 8N1) */
#define D621_BAUDRATE 9600

/* Linux-Debug: Geraetedatei, falls die Hazeltine-Bytefolge testweise
 * ueber eine echte serielle Schnittstelle am PC ausgegeben werden soll.
 * Fuer den normalen Debug-Betrieb (ANSI auf der virtuellen Konsole)
 * wird dieser Wert nicht benoetigt. */
#define D621_SERIELLE_SCHNITTSTELLE "/dev/ttyUSB0"

/* ESP32: Hardware-UART und Pins fuer die Verbindung zum Hazeltine
 * (ueber einen RS232-Pegelwandler wie den MAX3232). Es wird UART2
 * verwendet, damit UART0 frei fuer USB/Programmierung/Log bleibt. */
#define D621_ESP32_UART_NUM   2
#define D621_ESP32_RXD_PIN    16
#define D621_ESP32_TXD_PIN    17

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
#define D621_DEBUG_LOG_AKTIV 1
#define D621_DEBUG_BAUDRATE  115200

#endif
