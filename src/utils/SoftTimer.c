#include "SoftTimer.h"

#include "timeService.h"

#include <assert.h>
#include <stddef.h>

bool LAME_SoftTimer_Occur(LAME_SoftTimer *timer)
{
    if (timer->state == LAME_SoftTimer_StateStop) {
        return false;
    }

    if (timer->state == LAME_SoftTimer_StateElapsedComplete) {
        return true;
    }

    unsigned currentTime = millis();

    /* Таймер прошел. Переполнение должно само устраниться */
    unsigned dt = currentTime - timer->startTime;
    if (dt >= timer->period) {
        if (timer->mode == LAME_SoftTimer_ModePeriodic) {
            timer->startTime = currentTime;
        }
        else if (timer->mode == LAME_SoftTimer_ModeHardPeriodic) {
            if (dt > timer->period * 2) {
                timer->startTime = currentTime;
            }
            else {
                timer->startTime += timer->period;
            }
        }
        else {
            timer->state = LAME_SoftTimer_StateElapsedComplete;
        }
        return true;
    }

    return false;
}

void LAME_SoftTimer_Init(LAME_SoftTimer *timer, LAME_SoftTimer_Mode mode, unsigned period)
{
    timer->period = period;
    timer->mode   = mode;
    timer->state  = LAME_SoftTimer_StateStop;
}

LAME_SoftTimer_Mode LAME_SoftTimer_GetMode(const LAME_SoftTimer *timer)
{
    return timer->mode;
}

LAME_SoftTimer_State LAME_SoftTimer_GetState(const LAME_SoftTimer *timer)
{
    return timer->state;
}

void LAME_SoftTimer_Start(LAME_SoftTimer *timer)
{
    if (timer->state == LAME_SoftTimer_StateRun) {
        return;
    }
    timer->state     = LAME_SoftTimer_StateRun;
    timer->startTime = millis();
}

void LAME_SoftTimer_Stop(LAME_SoftTimer *timer)
{
    timer->state = LAME_SoftTimer_StateStop;
}

void LAME_SoftTimer_SetPeriod(LAME_SoftTimer *timer, unsigned period)
{
    timer->period = period;
}

unsigned LAME_SoftTimer_GetPeriod(const LAME_SoftTimer *timer)
{
    return timer->period;
}
