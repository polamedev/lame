#pragma once

#include <lame/drivers/Pin.h>

#include <stdbool.h>

typedef struct Led_Impl *Led;

/**
 * @brief  Создать диод
 * @param  pin: Дескриптор пина, должен быть всегда действителен
 * @param  activeLow: Активное положение - низкое
 * @param  blinkCount: Число миганий
 * @return Led - Дескриптор светодиода
 */
Led Led_Create(Pin pin, bool activeLow, unsigned blinkCount);

/**
 * @brief  Задача управления светодиодами
 */
void Led_Task();

/**
 * @brief  Установить количество миганий
 * @param  led: Дескриптор светодиода
 * @param  blinkCount: Количество миганий
 */
void Led_SetBlinkCount(Led led, unsigned blinkCount);

// TODO реализовать прямое управление диодом
void Led_SetActive(Led led, bool activeLow);
bool Led_GetActive(const Led led);