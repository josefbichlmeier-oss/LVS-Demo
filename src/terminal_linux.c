/*
 * D621-LVS
 *
 * Terminal-Treiber fuer den Linux-Debug-Build.
 *
 * Schreibt direkt per ANSI-Escapecodes auf stdout - entspricht
 * 1:1 der Ruby-Klasse LinuxTerminal (terminal/linux_terminal.rb).
 * Wird ausschliesslich auf einer virtuellen Konsole (Linux-VT)
 * verwendet, NICHT ueber eine serielle Verbindung.
 */

#include "platform.h"

#if defined(PLATFORM_LINUX)

#include <stdio.h>

#include "terminal.h"


void terminal_init(void)
{
    /* Kein Vorbereitungsschritt noetig - stdout ist bereits offen. */
}


void terminal_loeschen(void)
{
    printf("\033[2J");
    fflush(stdout);
}


void terminal_position(int x, int y)
{
    /* ANSI-Koordinaten sind 1-basiert, unser Modell 0-basiert. */
    printf("\033[%d;%dH", y + 1, x + 1);
    fflush(stdout);
}


void terminal_hell(void)
{
    printf("\033[33m");
    fflush(stdout);
}


void terminal_dunkel(void)
{
    printf("\033[37m");
    fflush(stdout);
}


void terminal_schreiben(const char *text)
{
    fputs(text, stdout);
    fflush(stdout);
}


void terminal_cursor_zurueck(void)
{
    printf("\010");
    fflush(stdout);
}


void terminal_zeile_loeschen(void)
{
    printf("\033[2K");
    fflush(stdout);
}


void terminal_zeichen_loeschen(void)
{
    printf(" \010");
    fflush(stdout);
}

#endif /* PLATFORM_LINUX */
