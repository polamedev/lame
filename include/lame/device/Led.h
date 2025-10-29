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
 * @param  blinkCount: Количество миганий
 */
void Led_SetBlinkCount(Led led, unsigned blinkCount);

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


#ifdef __cplusplus
}
#endif
