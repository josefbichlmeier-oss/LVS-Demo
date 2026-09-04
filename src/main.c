/*
 * D621-LVS
 *
 * Linux-Debug-Einstiegspunkt. Wird ausschliesslich fuer den
 * Debug-Build (gcc, virtuelle Konsole) verwendet - fuer den
 * ESP32-Zielbetrieb siehe arduino/d621_lvs/d621_lvs.ino.
 */

#include "platform.h"

#if defined(PLATFORM_LINUX)

#include "anwendung.h"


int main(void)
{
    anwendung_start();

    return 0;
}

#endif
