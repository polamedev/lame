#include "SoftTimer.h"

#include "timeService.h"

#include <assert.h>
#include <stddef.h>

bool SoftTimer_Occur(SoftTimer *timer)
{
    if (timer->state == SoftTimer_StateStop) {
        return false;
    }

    if (timer->state == SoftTimer_StateElapsedComplete) {
        return true;
    }

    unsigned currentTime = millis();

    /* Таймер прошел. Переполнение должно само устраниться */
    unsigned dt = currentTime - timer->startTime;
    if (dt >= timer->period) {
        if (timer->mode == SoftTimer_ModePeriodic) {
            timer->startTime = currentTime;
        }
        else if (timer->mode == SoftTimer_ModeHardPeriodic) {
            if (dt > timer->period * 2) {
                timer->startTime = currentTime;
            }
            else {
                timer->startTime += timer->period;
            }
        }
        else {
            timer->state = SoftTimer_StateElapsedComplete;
        }
        return true;
    }

    return false;
}

void SoftTimer_Init(SoftTimer *timer, SoftTimer_Mode mode, unsigned period)
{
    timer->period = period;
    timer->mode   = mode;
    timer->state  = SoftTimer_StateStop;
}

SoftTimer_Mode SoftTimer_GetMode(const SoftTimer *timer)
{
    return timer->mode;
}

SoftTimer_State SoftTimer_GetState(const SoftTimer *timer)
{
    return timer->state;
}

void SoftTimer_Start(SoftTimer *timer)
{
    if (timer->state == SoftTimer_StateRun) {
        return;
    }
    timer->state     = SoftTimer_StateRun;
    timer->startTime = millis();
}

void SoftTimer_Stop(SoftTimer *timer)
{
    timer->state = SoftTimer_StateStop;
}

void SoftTimer_SetPeriod(SoftTimer *timer, unsigned period)
{
    timer->period = period;
}

unsigned SoftTimer_GetPeriod(const SoftTimer *timer)
{
    return timer->period;
}
