#include "platform.h"

#if defined(PLATFORM_ESP32)

#include <Arduino.h>
#include <stdio.h>

extern "C" {
#include "zeit_port.h"
}


void zeit_text(char *puffer, size_t groesse)
{
    unsigned long gesamt_sekunden = millis() / 1000UL;

    unsigned int stunden  = (gesamt_sekunden / 3600UL) % 100UL;
    unsigned int minuten  = (gesamt_sekunden / 60UL) % 60UL;
    unsigned int sekunden = gesamt_sekunden % 60UL;

    snprintf(
        puffer,
        groesse,
        "LZ %02u:%02u:%02u",
        stunden,
        minuten,
        sekunden
    );
}

#endif
