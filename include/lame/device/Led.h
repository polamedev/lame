#pragma once

#ifdef __cplusplus
extern "C" {
#endif

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

bool Led_IsActive(const Led led);
void Led_SetActive(Led led, bool state);
void Led_Toggle(Led led);

#ifdef __cplusplus
}
#endif
