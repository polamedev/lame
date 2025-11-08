#include "Led.h"

// TODO
// #include <lame_config.h>

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

// TODO LEDS_QTY задавать из конфига
#define LEDS_QTY 5

static Led_Impl leds[LEDS_QTY];
static size_t   freeLedIndex = 0;

const unsigned shortBlinkTime = 100;
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
    (void) self;
    freeLedIndex--;
}

bool Led_Read(const Led led)
{
    return led->isActive;
}

void Led_Write(Led led, bool active)
{
    led->isActive = active;
    if (led->activeLow) {
        active = !active;
    }

    Pin_Write(led->pin, active);
}

void Led_Toggle(Led led)
{
    if (Led_Read(led)) {
        Led_Write(led, false);
    }
    else {
        Led_Write(led, true);
    }
}

static void Led_UnitTask(Led led)
{
    if (!SoftTimer_Occur(&led->timer)) {
        return;
    }

    Led_Toggle(led);

    led->nextStage++;
    if (led->nextStage >= led->blinkStages) {
        led->nextStage = 0;
    }

    SoftTimer_SetPeriod(&led->timer, led->nextStage == 0 ? longBlinkTime : shortBlinkTime);
}

void Led_Task()
{
    for (size_t i = 0; i < freeLedIndex; ++i) {
        Led_UnitTask(&leds[i]);
    }
}

void Led_StartBlink(Led led)
{
    led->nextStage = 1;
    Led_Write(led, true);
    SoftTimer_SetPeriod(&led->timer, shortBlinkTime);
    SoftTimer_Start(&led->timer);
}

void Led_SetBlinkCount(Led led, unsigned blinkCount)
{
    led->blinkStages = blinkCount * 2;
}
