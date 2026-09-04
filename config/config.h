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

#endif
