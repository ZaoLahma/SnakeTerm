#include "../../inc/game_time.h"

#include <time.h>
#include <sys/time.h>

uint64_t getGameMicroSecTime (void)
{
    struct timespec ts;
    uint64_t retVal = 0;

    if(clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
    {
        retVal = (uint64_t) (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
    }

    return retVal;
}
