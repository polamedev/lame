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

/**
 * @brief  Запуск мигания. Сразу после запуска светодиод будет активным
 */
void Led_StartBlink(Led);

/**
 * @brief  Остановка мигания. после остановки светодиод будет выключенным
 */
void Led_StopBlink(Led);

/**
 * @brief  Проверка запущено ли мигание
 * @return true - Мигание запущено
 * @return false - Мигание остановлено
 */
bool Led_IsBlinkRunning(Led);

/**
 * @brief  Установить количество миганий
 * @param  blinkCount: Количество миганий
 */
void Led_SetBlinkCount(Led, unsigned blinkCount);

/**
 * @brief  Вернуть количество миганий
 * @return unsigned - Установленное количество миганий
 */
unsigned Led_GetBlinkCount(const Led);


#ifdef __cplusplus
}
#endif
