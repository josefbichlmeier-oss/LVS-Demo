#include "platform.h"

#if defined(PLATFORM_LINUX)

#include <time.h>
#include <stdio.h>

#include "zeit_port.h"


void zeit_text(char *puffer, size_t groesse)
{
    time_t jetzt = time(NULL);
    struct tm *lokal = localtime(&jetzt);

    if (lokal == NULL)
    {
        snprintf(puffer, groesse, "%s", "");
        return;
    }

    strftime(puffer, groesse, "%d.%m.%Y %H:%M", lokal);
}

#endif
