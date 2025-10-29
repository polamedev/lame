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
 * @return Led - Дескриптор светодиода
 */
Led Led_Create(Pin pin, bool activeLow);

Led Led_Destroy(Led);


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

// TODO Сделать поддержку следующих функций   activeLow: Активное положение - низкое ; blinkCount: Число миганий


#ifdef __cplusplus
}
#endif
