#include <stdio.h>
#include <string.h>

#include "../config/config.h"
#include "bildschirm.h"


static char daten[D621_HOEHE][D621_BREITE];

static int cursor_x;
static int cursor_y;


void bildschirm_initialisieren(void)
{
    bildschirm_loeschen();

    cursor_x = 0;
    cursor_y = 0;
}


void bildschirm_loeschen(void)
{
    for (int y = 0; y < D621_HOEHE; y++)
    {
        for (int x = 0; x < D621_BREITE; x++)
        {
            daten[y][x] = ' ';
        }
    }
}


void bildschirm_schreiben(
    int x,
    int y,
    const char *text
)
{
    if (y < 0 || y >= D621_HOEHE)
        return;

    for (int i = 0; text[i] != '\0'; i++)
    {
        int xpos = x + i;

        if (xpos < 0)
            continue;

        if (xpos >= D621_BREITE)
            break;

        daten[y][xpos] = text[i];
    }
}


void bildschirm_cursor(
    int x,
    int y
)
{
    if (x >= 0 && x < D621_BREITE)
        cursor_x = x;

    if (y >= 0 && y < D621_HOEHE)
        cursor_y = y;
}


void bildschirm_ausgeben(void)
{
    printf("\033[2J");
    printf("\033[H");

    for (int y = 0; y < D621_HOEHE; y++)
    {
        fwrite(
            daten[y],
            1,
            D621_BREITE,
            stdout
        );

        putchar('\n');
    }

    fflush(stdout);
}
