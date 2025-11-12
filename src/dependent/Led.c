#include "Led.h"

#include <lameConfig.h>

#include <lame/utils/SoftTimer.h>

#include <stddef.h>

typedef struct Led_Impl {
    Pin       pin;
    bool      activeLow;
    bool      isActive;
    unsigned  blinkStages; // Общее число стадий миганий
    unsigned  nextStage;   // Следующая стадия мигания
    SoftTimer timer;
} Led_Impl;

#define LEDS_QTY LAME_CONF_LEDS_QTY

static Led_Impl leds[LEDS_QTY];
static size_t   freeLedIndex = 0;

const unsigned shortBlinkTime = 150;
const unsigned longBlinkTime  = shortBlinkTime * 5;

static void Led_Init(Led self, Pin pin, bool activeLow)
{
    self->pin       = pin;
    self->isActive  = false;
    self->activeLow = activeLow;
    self->nextStage = 0;

    Led_Write(self, activeLow);
    Led_SetBlinkCount(self, 1);
    SoftTimer_Init(&self->timer, SoftTimer_ModePeriodic, shortBlinkTime);
}

Led Led_Create(Pin pin, bool activeLow)
{
    if (freeLedIndex == LEDS_QTY) {
        return NULL;
    }
    Led led = &leds[freeLedIndex];
    freeLedIndex++;

    Led_Init(led, pin, activeLow);
    return led;
}

void Led_Destroy(Led self)
{
    (void)self;
    freeLedIndex--;
}

bool Led_Read(const Led self)
{
    return self->isActive;
}

void Led_Write(Led self, bool active)
{
    self->isActive = active;
    if (self->activeLow) {
        active = !active;
    }

    Pin_Write(self->pin, active);
}

void Led_Toggle(Led self)
{
    if (Led_Read(self)) {
        Led_Write(self, false);
    }
    else {
        Led_Write(self, true);
    }
}

static void Led_UnitTask(Led self)
{
    if (!SoftTimer_Occur(&self->timer)) {
        return;
    }

    Led_Toggle(self);

    self->nextStage++;
    if (self->nextStage >= self->blinkStages) {
        self->nextStage = 0;
    }

    SoftTimer_SetPeriod(&self->timer, self->nextStage == 0 ? longBlinkTime : shortBlinkTime);
}

void Led_Task()
{
    for (size_t i = 0; i < freeLedIndex; ++i) {
        Led_UnitTask(&leds[i]);
    }
}

void Led_StartBlink(Led self)
{
    self->nextStage = 1;
    Led_Write(self, true);
    SoftTimer_SetPeriod(&self->timer, shortBlinkTime);
    SoftTimer_Start(&self->timer);
}

void Led_StopBlink(Led self)
{
    Led_Write(self, false);
    SoftTimer_Stop(&self->timer);
}

bool Led_IsBlinkRunning(Led self)
{
    return SoftTimer_GetState(&self->timer) == SoftTimer_StateRun;
}

void Led_SetBlinkCount(Led self, unsigned blinkCount)
{
    self->blinkStages = blinkCount * 2;

    if (Led_IsBlinkRunning(self)) {
        Led_StopBlink(self);
        Led_StartBlink(self);
    }
}

unsigned Led_GetBlinkCount(const Led self)
{
    return self->blinkStages / 2;
}
