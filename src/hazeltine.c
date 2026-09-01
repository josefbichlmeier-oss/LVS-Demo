#include <stdio.h>
#include <unistd.h>

#include "hazeltine.h"


int hazeltine_oeffnen(const char *geraet)
{
    printf("Hazeltine: %s\n", geraet);

    return 0;
}


void hazeltine_schliessen(void)
{
}


void hazeltine_loeschen(void)
{
    const char sequenz[] =
        "\x7E\x1C"
        "\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F";

    printf("CLEAR: ");

    for (size_t i = 0; i < sizeof(sequenz) - 1; i++)
        printf("%02X ", (unsigned char)sequenz[i]);

    printf("\n");
}


void hazeltine_position(int x, int y)
{
    printf("POSITION: %d,%d\n", x, y);
}


void hazeltine_hell(void)
{
    printf("HELL\n");
}


void hazeltine_dunkel(void)
{
    printf("DUNKEL\n");
}


void hazeltine_schreiben(const char *text)
{
    printf("TEXT: %s\n", text);
}
