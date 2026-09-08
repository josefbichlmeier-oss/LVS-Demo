#include "platform.h"

#if defined(PLATFORM_LINUX)

#include "../config/config.h"
#include "debug_log.h"

#if D621_DEBUG_LOG_AKTIV

#include <stdio.h>
#include <stdarg.h>


void debug_log_init(void)
{
    /* stderr ist bereits offen - kein Vorbereitungsschritt noetig. */
}


void debug_log(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fputc('\n', stderr);
}

#else /* !D621_DEBUG_LOG_AKTIV */

void debug_log_init(void) {}
void debug_log(const char *format, ...) { (void)format; }

#endif

#endif /* PLATFORM_LINUX */
