/*
 * D621-LVS
 *
 * ESP32/Arduino-Einstiegspunkt (setup()/loop()).
 *
 * Bewusst getrennt von main.c (Linux-Debug), damit auf dem
 * Mikrocontroller kein main() aus main.c mitkompiliert wird -
 * die Arduino-Laufzeitumgebung bringt ihr eigenes main() mit,
 * das setup() einmalig und loop() danach endlos aufruft.
 */

#include "platform.h"

#if defined(PLATFORM_ESP32)

#include <Arduino.h>

extern "C" {
#include "anwendung.h"
}


void setup()
{
    anwendung_init();
}


void loop()
{
    /* Eine komplette Sitzung (Start -> Anmeldung -> Hauptmenue, bis
     * Abmeldung/ESC). Kehrt anwendung_sitzung() zurueck, ruft
     * Arduino loop() sie sofort erneut auf - das Geraet springt
     * dann wieder zum Startbildschirm, statt "haengenzubleiben". */
    anwendung_sitzung();
}

#endif
