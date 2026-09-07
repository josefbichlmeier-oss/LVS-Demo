/*
 * D621-LVS
 *
 * UART-Anbindung fuer den ESP32 (Arduino-Core).
 *
 * Nutzt den zweiten Hardware-UART (Serial2) des ESP32. Dieser wird
 * ueber einen RS232-Pegelwandler (z.B. MAX3232) an den seriellen
 * Anschluss des Hazeltine 2000A/B angeschlossen. UART0 (Serial)
 * bleibt dadurch frei fuer USB/Flashen und - bei Bedarf - fuer
 * eine zusaetzliche Log-Ausgabe waehrend der Entwicklung.
 *
 * Pinbelegung und Baudrate kommen aus config/config.h.
 */

#include "platform.h"

#if defined(PLATFORM_ESP32)

#include <Arduino.h>

extern "C" {
#include "uart_port.h"
#include "../config/config.h"
}


static unsigned long g_tx_bytes = 0;
static unsigned long g_rx_bytes = 0;
static unsigned char g_letztes_byte = 0;


void uart_port_init(void)
{
    Serial2.begin(
        D621_BAUDRATE,
        SERIAL_8N1,
        D621_ESP32_RXD_PIN,
        D621_ESP32_TXD_PIN
    );
}


void uart_port_write(const char *data, size_t len)
{
    Serial2.write(
        reinterpret_cast<const uint8_t *>(data),
        len
    );
    Serial2.flush();

    g_tx_bytes += len;
}


int uart_port_read_byte(unsigned char *out)
{
    if (Serial2.available() <= 0)
    {
        return 0;
    }

    int wert = Serial2.read();

    if (wert < 0)
    {
        return 0;
    }

    *out = (unsigned char)wert;

    g_rx_bytes++;
    g_letztes_byte = *out;

    return 1;
}


void uart_port_delay_ms(unsigned int ms)
{
    /* delay() speist innerhalb dessen auch den Watchdog und laesst
     * WLAN/Hintergrund-Tasks des ESP32 laufen - wichtig, da die
     * Tastaturschleife hierueber gepollt wird. */
    delay(ms);
}


void uart_port_diagnose(
    unsigned long *tx_bytes,
    unsigned long *rx_bytes,
    unsigned char *letztes_byte
)
{
    *tx_bytes = g_tx_bytes;
    *rx_bytes = g_rx_bytes;
    *letztes_byte = g_letztes_byte;
}

#endif /* PLATFORM_ESP32 */
