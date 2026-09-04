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

#ifdef __cplusplus
}
#endif

#endif
