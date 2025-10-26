#include "timeServiceMock.hpp"

static unsigned msecMillis = 0; 

extern "C" {
    unsigned millis() {
        return msecMillis;
    }
}

void millis_set(unsigned msec)
{
    msecMillis = msec;
}

