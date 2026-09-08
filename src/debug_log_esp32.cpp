#include "platform.h"

#if defined(PLATFORM_ESP32)

#include "../config/config.h"

extern "C" {
#include "debug_log.h"
}

#if D621_DEBUG_LOG_AKTIV

#include <Arduino.h>
#include <cstdarg>
#include <cstdio>


void debug_log_init(void)
{
    /* UART0 (Serial) - der USB/Programmierstecker. Voellig
     * unabhaengig von Serial2 (UART2, Hazeltine). */
    Serial.begin(D621_DEBUG_BAUDRATE);
}


void debug_log(const char *format, ...)
{
    char puffer[160];
    va_list args;

    va_start(args, format);
    vsnprintf(puffer, sizeof(puffer), format, args);
    va_end(args);

    Serial.println(puffer);
}

#else /* !D621_DEBUG_LOG_AKTIV */

void debug_log_init(void) {}
void debug_log(const char *format, ...) { (void)format; }

#endif

#endif /* PLATFORM_ESP32 */
