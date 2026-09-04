#include <stdio.h>
#include <string.h>

#include "bildschirm.h"
#include "terminal.h"

static char bildschirm[BILDSCHIRMHOEHE][BILDSCHIRMBREITE];

void bildschirm_loeschen(void)
{
    int y;

    for (y = 0; y < BILDSCHIRMHOEHE; y++)
    {
        memset(
            bildschirm[y],
            ' ',
            BILDSCHIRMBREITE
        );
    }

    terminal_loeschen();
}

void bildschirm_text(
    int x,
    int y,
    const char *text
)
{
    int i;

    if (x < 0 || x >= BILDSCHIRMBREITE)
        return;

    if (y < 0 || y >= BILDSCHIRMHOEHE)
        return;

    for (i = 0;
         text[i] != '\0' &&
         x + i < BILDSCHIRMBREITE;
         i++)
    {
        bildschirm[y][x + i] = text[i];
    }
}

void bildschirm_ausgeben(void)
{
    int x;
    int y;

    for (y = 0; y < BILDSCHIRMHOEHE; y++)
    {
        terminal_positionieren(0, y);

        for (x = 0; x < BILDSCHIRMBREITE; x++)
        {
            putchar(bildschirm[y][x]);
        }
    }

    fflush(stdout);
}
