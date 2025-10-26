#include "Event.h"

void Event_Init(Event *event)
{
    Event_Clear(event);
}

bool Event_Take(Event *event)
{
    if (*event) {
        *event = false;
        return true;
    }
    else {
        return false;
    }
}

bool Event_Check(const Event *event)
{
    return *event;
}
void Event_Set(Event *event)
{
    *event = true;
}

void Event_Clear(Event *event)
{
    *event = false;
}
