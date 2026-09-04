#include <stdio.h>

#include "terminal.h"

void terminal_loeschen(void)
{
    printf("\033[2J");
    printf("\033[H");
}

void terminal_positionieren(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

void terminal_text(const char *text)
{
    printf("%s", text);
}

void terminal_hell(void)
{
    printf("\033[1m");
}

void terminal_dunkel(void)
{
    printf("\033[2m");
}
