#include "Led.h"

// TODO
// #include <lame_config.h>

#include <lame/utils/SoftTimer.h>

#include <stddef.h>

typedef struct Led_Impl {
    Pin       pin;
    bool      activeLow;
    bool      isActive;
    unsigned  blinkCount;
    unsigned  currentCount;
    SoftTimer timer;
} Led_Impl;

// TODO LEDS_QTY задавать из конфига
#define LEDS_QTY 5

static Led_Impl leds[LEDS_QTY];
static size_t   freeLed = 0;

const unsigned blinkTime = 100;

static void Led_UnitTask(Led led)
{
    if (!SoftTimer_Occur(&led->timer)) {
        return;
    }

    if (led->currentCount % 2 == 0) {
        Led_SetActive(led, true);
    }
    else {
        Led_SetActive(led, false);
    }

    led->currentCount++;

    if (led->currentCount >= led->blinkCount) {
        led->currentCount = 0;
        SoftTimer_SetPeriod(&led->timer, blinkTime * 5);
    }
    else {
        SoftTimer_SetPeriod(&led->timer, blinkTime);
    }
}

Led Led_Create(Pin pin, bool activeLow, unsigned blinkCount)
{
    if (freeLed == LEDS_QTY) {
        return NULL;
    }
    Led led = &leds[freeLed];
    freeLed++;

    led->pin          = pin;
    led->isActive     = false;
    led->activeLow    = activeLow;
    led->blinkCount   = blinkCount * 2;
    led->currentCount = 0;

    Led_SetActive(led, activeLow);

    SoftTimer_Init(&led->timer, SoftTimer_ModePeriodic, blinkTime);
    SoftTimer_Start(&led->timer);

    return led;
}

void Led_Task()
{
    for (size_t i = 0; i < freeLed; ++i) {
        Led_UnitTask(&leds[i]);
    }
}

bool Led_IsActive(const Led led)
{
    return led->isActive;
}

void Led_SetActive(Led led, bool active)
{
    led->isActive = active;
    if (led->activeLow) {
        active = !active;
    }

    Pin_Write(led->pin, active);
}

void Led_Toggle(Led led)
{
    if (Led_IsActive(led)) {
        Led_SetActive(led, false);
    }
    else {
        Led_SetActive(led, true);
    }
}

void Led_SetBlinkCount(Led led, unsigned blinkCount)
{
    led->blinkCount = blinkCount;
}
