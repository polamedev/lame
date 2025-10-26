#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef bool Event;

/**
 * @brief  Инициализация события
 * @param  event: дескриптор события
 */
void Event_Init(Event *event);

/**
 * @brief  Получить событие, событие сбросится, если оно произошло
 * @param  event: дескриптор события
 * @return true - событие произошло
 * @return false - событие не произошло
 */
bool Event_Take(Event *event);

/**
 * @brief  Проверить событие
 * @param  event: дескриптор события
 * @return true - событие произошло
 * @return false - событие не произошло
 */
bool Event_Check(const Event *event);

/**
 * @brief  Установить событие
 * @param  event: дескриптор события
 */
void Event_Set(Event *event);

/**
 * @brief  Сбросить событие
 * @param  event: дескриптор события
 */
void Event_Clear(Event *event);

#ifdef __cplusplus
}
#endif