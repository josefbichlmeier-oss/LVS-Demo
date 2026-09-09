/*
 * D621-LVS
 *
 * Terminal-Treiber fuer ein DEC VT220 - Zielplattform ESP32.
 *
 * Das VT220 ist abwaertskompatibel zu VT100/ANSI und versteht
 * dieselben Steuersequenzen wie die lokale ANSI-Konsole
 * (terminal_linux.c) - hier werden sie statt auf stdout ueber die
 * serielle UART-Verbindung (RS232 -> MAX3232) gesendet. Anders als
 * bei terminal_linux.c (xterm-Farbcodes 33/37 fuer die
 * Hervorhebung) wird fuer "hell"/"dunkel" bewusst Invers-Video
 * (SGR 7) verwendet: echte VT220-Hardware ist monochrom und kennt
 * keine ANSI-Farbcodes, Invers-Video ist dagegen Teil des
 * VT100/VT220-Standards und auf jedem echten Geraet zuverlaessig
 * sichtbar.
 *
 * Verwendete Sequenzen (alle Standard-ANSI/VT100, 1-basierte
 * Koordinaten):
 *
 *   Loeschen        : ESC [ 2 J             (kompletter Bildschirm)
 *   Position x,y    : ESC [ <y+1> ; <x+1> H
 *   Hell (invers)   : ESC [ 7 m
 *   Dunkel (normal) : ESC [ 0 m
 *   Zeile loeschen  : ESC [ 2 K
 *   Zeichen loeschen: <space> + Backspace (VT220 kennt kein
 *                     einzelnes "Zeichen loeschen unter Cursor" in
 *                     der Minimalauspraegung, die hier genutzt
 *                     wird - Leerzeichen ueberschreiben + zurueck
 *                     ist auf jedem VT100/220 zuverlaessig)
 *   Cursor zurueck  : BS (0x08)
 */

#include "platform.h"

#if defined(PLATFORM_ESP32)

#include "../config/config.h"

#if D621_ESP32_TERMINAL == D621_TERMINAL_VT220

#include <stdio.h>
#include <string.h>

#include "terminal.h"
#include "uart_port.h"


static void schreiben(const char *text)
{
    uart_port_write(text, strlen(text));
}


void terminal_init(void)
{
    uart_port_init();
}


void terminal_loeschen(void)
{
    schreiben("\033[2J");
}


void terminal_position(int x, int y)
{
    char sequenz[16];

    /* VT220-Koordinaten sind wie ANSI 1-basiert, unser Modell
     * 0-basiert. */
    snprintf(sequenz, sizeof(sequenz), "\033[%d;%dH", y + 1, x + 1);

    schreiben(sequenz);
}


void terminal_hell(void)
{
    schreiben("\033[7m");
}


void terminal_dunkel(void)
{
    schreiben("\033[0m");
}


void terminal_schreiben(const char *text)
{
    schreiben(text);
}


void terminal_cursor_zurueck(void)
{
    schreiben("\010");
}


void terminal_zeile_loeschen(void)
{
    schreiben("\033[2K");
}


void terminal_zeichen_loeschen(void)
{
    schreiben(" \010");
}

#endif /* D621_ESP32_TERMINAL == D621_TERMINAL_VT220 */

#endif /* PLATFORM_ESP32 */
