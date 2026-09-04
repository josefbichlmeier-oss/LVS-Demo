/*
 * D621-LVS
 *
 * Tastatur-Treiber fuer den Linux-Debug-Build.
 *
 * Versetzt das Terminal in den Raw-Modus (kein Kanonik-Modus, kein
 * Echo) und liest zeichenweise - entspricht Ruby STDIN.getch
 * (terminal/linux_tastatur.rb). Der urspruengliche Modus wird beim
 * Programmende automatisch wiederhergestellt.
 */

#include "platform.h"

#if defined(PLATFORM_LINUX)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "tastatur.h"


static struct termios alter_modus;
static int modus_gesichert = 0;


static void modus_wiederherstellen(void)
{
    if (modus_gesichert)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &alter_modus);
    }
}


void tastatur_init(void)
{
    struct termios neuer_modus;

    if (tcgetattr(STDIN_FILENO, &alter_modus) == 0)
    {
        modus_gesichert = 1;
        atexit(modus_wiederherstellen);

        neuer_modus = alter_modus;

        neuer_modus.c_lflag &= ~(ICANON | ECHO);
        neuer_modus.c_cc[VMIN] = 1;
        neuer_modus.c_cc[VTIME] = 0;

        tcsetattr(STDIN_FILENO, TCSANOW, &neuer_modus);
    }
}


char tastatur_lesen(void)
{
    int zeichen = getchar();

    if (zeichen == EOF)
    {
        /* z.B. Eingabe per Pipe/Umleitung zu Ende - Programm sauber
         * beenden statt in einer Endlosschleife haengen zu bleiben. */
        exit(0);
    }

    return (char)zeichen;
}

#endif /* PLATFORM_LINUX */
