#include "platform.h"

#if defined(PLATFORM_ESP32)

#include <Arduino.h>

extern "C" {
#include "monotonzeit.h"
}


unsigned long monotonzeit_sekunden(void)
{
    return millis() / 1000UL;
}

#endif
