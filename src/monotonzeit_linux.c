#include "platform.h"

#if defined(PLATFORM_LINUX)

#define _POSIX_C_SOURCE 199309L

#include <time.h>

#include "monotonzeit.h"


unsigned long monotonzeit_sekunden(void)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
    {
        return 0;
    }

    return (unsigned long)ts.tv_sec;
}

#endif
