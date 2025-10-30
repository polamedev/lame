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

void Led_Destroy(Led);

/**
 * @brief  Прочитать логическое состояние
 * @return true - Диод включен 
 * @return false - Диод выключен
 */
bool Led_Read(const Led);

/**
 * @brief  Записать логическое состояние
 * @param  state: 
 */
void Led_Write(Led, bool state);

/**
 * @brief  Изменить логическое состояние светодиода
 */
void Led_Toggle(Led);

// TODO Сделать поддержку следующих функций   activeLow: Активное положение - низкое ; blinkCount: Число миганий


/**
 * @brief  Задача управления светодиодами
 */
void Led_Task();

void Led_StartBlink(Led);

/**
 * @brief  Установить количество миганий
 * @param  blinkCount: Количество миганий
 */
void Led_SetBlinkCount(Led led, unsigned blinkCount);

#ifdef __cplusplus
}
#endif
