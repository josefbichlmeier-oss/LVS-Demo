/*
 * D621-LVS
 *
 * Tastatur-Treiber fuer den Hazeltine 2000A/B - Zielplattform ESP32.
 *
 * Tasteneingaben kommen - wie beim Original - ueber dieselbe
 * serielle Leitung zurueck, auf der auch die Bildschirmausgabe
 * gesendet wird (entspricht Ruby HazeltineTastatur#lesen, das per
 * Polling-Schleife mit sleep(0.01) auf SerielleSchnittstelle#empfangen
 * wartet).
 */

#include "platform.h"

#if defined(PLATFORM_ESP32)

#include "tastatur.h"
#include "uart_port.h"


void tastatur_init(void)
{
    /* UART wird bereits von terminal_init() (terminal_hazeltine.c)
     * initialisiert - beide teilen sich dieselbe Schnittstelle. */
}


char tastatur_lesen(void)
{
    unsigned char taste;

    for (;;)
    {
        if (uart_port_read_byte(&taste))
        {
            return (char)taste;
        }

        uart_port_delay_ms(10);
    }
}

#endif /* PLATFORM_ESP32 */
