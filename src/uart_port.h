/*
 * D621-LVS
 *
 * Duenne UART-Portierungsschicht fuer die ESP32/Arduino-Seite.
 *
 * Wird von terminal_hazeltine.c (Ausgabe zum Hazeltine) und von
 * tastatur_hazeltine.c (Tastatureingaben vom Hazeltine, kommen
 * ueber dieselbe Leitung zurueck - wie in der Ruby-Vorlage, wo
 * SerielleSchnittstelle sowohl senden() als auch empfangen()
 * anbietet) gemeinsam genutzt.
 *
 * Implementiert in uart_port_esp32.cpp (Arduino HardwareSerial,
 * UART2 -> MAX3232 -> Hazeltine 2000A/B).
 */

#ifndef D621_UART_PORT_H
#define D621_UART_PORT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void uart_port_init(void);

void uart_port_write(const char *data, size_t len);

/* Liefert 1 und schreibt das Byte nach *out, wenn eines verfuegbar
 * war; liefert 0, wenn (aktuell) kein Byte anliegt. Nicht
 * blockierend - das Warten auf Tastendruck erledigt die
 * aufrufende Tastaturschicht per Polling-Schleife. */
int uart_port_read_byte(unsigned char *out);

void uart_port_delay_ms(unsigned int ms);

/*
 * Nur fuer das optionale Nokia-5110-Diagnose-Display gedacht
 * (siehe config.h D621_NOKIA5110_AKTIV) - liefert einfache
 * Betriebszaehler seit dem letzten Start:
 *
 *   *tx_bytes     Anzahl ueber uart_port_write() gesendeter Bytes
 *   *rx_bytes     Anzahl ueber uart_port_read_byte() empfangener Bytes
 *   *letztes_byte zuletzt empfangenes Byte (0, falls noch keins da war)
 *
 * Rein additiv - hat keinerlei Einfluss auf die eigentliche
 * Terminal-/Tastaturfunktion.
 */
void uart_port_diagnose(
    unsigned long *tx_bytes,
    unsigned long *rx_bytes,
    unsigned char *letztes_byte
);

#ifdef __cplusplus
}
#endif

#endif
