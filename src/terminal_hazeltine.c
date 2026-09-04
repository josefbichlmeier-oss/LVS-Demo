/*
 * D621-LVS
 *
 * Terminal-Treiber fuer den Hazeltine 2000A/B - Zielplattform ESP32.
 *
 * Bytefolgen 1:1 aus der Ruby-Vorlage uebernommen
 * (terminal/hazeltine2000ab.rb):
 *
 *   Loeschen     : 7E 1C 7F 7F 7F 7F 7F 7F 7F 7F 7F
 *   Position x,y : 7E 11 <adr(x)> <adr(y)>
 *   Hell         : 7E 1F
 *   Dunkel       : 7E 19
 *   Zeile loeschen: 7E 13
 *   Zeichen loeschen: 7F
 *   Cursor zurueck: 08
 *
 * Adressumrechnung (siehe private Methode "adresse" im Original):
 * Werte < 32 werden um 96 erhoeht, da das Hazeltine-Protokoll den
 * Adressbereich 0..31 nicht direkt per Steuerzeichen uebertragen
 * kann (diese Werte kollidieren mit anderen Steuerzeichen).
 */

#include "platform.h"

#if defined(PLATFORM_ESP32)

#include <string.h>

#include "terminal.h"
#include "uart_port.h"


static unsigned char adresse(int wert)
{
    if (wert < 32)
    {
        return (unsigned char)(wert + 96);
    }

    return (unsigned char)wert;
}


void terminal_init(void)
{
    uart_port_init();
}


void terminal_loeschen(void)
{
    const char sequenz[] =
        "\x7E\x1C\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F";

    uart_port_write(sequenz, sizeof(sequenz) - 1);
    uart_port_delay_ms(20);
}


void terminal_position(int x, int y)
{
    char sequenz[4];

    sequenz[0] = '\x7E';
    sequenz[1] = '\x11';
    sequenz[2] = (char)adresse(x);
    sequenz[3] = (char)adresse(y);

    uart_port_write(sequenz, sizeof(sequenz));
}


void terminal_hell(void)
{
    const char sequenz[] = "\x7E\x1F";

    uart_port_write(sequenz, sizeof(sequenz) - 1);
}


void terminal_dunkel(void)
{
    const char sequenz[] = "\x7E\x19";

    uart_port_write(sequenz, sizeof(sequenz) - 1);
}


void terminal_schreiben(const char *text)
{
    uart_port_write(text, strlen(text));
}


void terminal_cursor_zurueck(void)
{
    const char sequenz[] = "\x08";

    uart_port_write(sequenz, sizeof(sequenz) - 1);
}


void terminal_zeile_loeschen(void)
{
    const char sequenz[] = "\x7E\x13";

    uart_port_write(sequenz, sizeof(sequenz) - 1);
    uart_port_delay_ms(10);
}


void terminal_zeichen_loeschen(void)
{
    const char sequenz[] = "\x7F";

    uart_port_write(sequenz, sizeof(sequenz) - 1);
}

#endif /* PLATFORM_ESP32 */
