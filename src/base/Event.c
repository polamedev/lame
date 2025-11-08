#include "Event.h"

#include <stddef.h>



// #define EVENT_IMPLEMENTS_CONT 5
// struct EventImpl eventImplements[EVENT_IMPLEMENTS_CONT];
// int              count = 0;

// Event Event_Create()
// {
//     if (count < EVENT_IMPLEMENTS_CONT) {
//         Event *event = &eventImplements[count];
//         Event_Init(event);
//         count += 1;
//         return event;
//     }
//     return NULL;
// }

void Event_Init(Event *event)
{
    Event_Clear(event);
}

bool Event_Take(Event *event)
{
    if (event->val) {
        event->val = false;
        return true;
    }
    else {
        return false;
    }
}

bool Event_Check(const Event *event)
{
    return event->val;
}
void Event_Set(Event *event)
{
    event->val = true;
}

void Event_Clear(Event *event)
{
    event->val = false;
}
