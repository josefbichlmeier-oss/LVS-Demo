#include <stdio.h>

#include "../config/config.h"
#include "hazeltine.h"
#include "bildschirm.h"


int main(void)
{
    printf("D621-LVS C\n");

    bildschirm_initialisieren();

    bildschirm_schreiben(
        20,
        10,
        "D621-LVS C"
    );

    bildschirm_schreiben(
        25,
        12,
        "ESP32 VERSION"
    );

    bildschirm_cursor(
        0,
        0
    );

    bildschirm_ausgeben();

    return 0;
}
