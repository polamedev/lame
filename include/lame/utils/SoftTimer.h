#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum {
    SoftTimer_ModePeriodic,     // Режим периодического срабатывания
    SoftTimer_ModeHardPeriodic, // Режим жесткого периодического срабатывания, срабатывания будут происходить независимо от проверки SoftTimer_Occur
    SoftTimer_ModeElapsed,      // Режим срабатывания один раз
} SoftTimer_Mode;

typedef enum {
    SoftTimer_StateStop,            // Таймер остановлен
    SoftTimer_StateRun,             // Таймер запущен
    SoftTimer_StateElapsedComplete, // Таймер завершен в режим elapsed
} SoftTimer_State;

typedef struct SoftTimer {
    unsigned        startTime; // Начальное время старта
    unsigned        period;    // Период истечения таймера
    SoftTimer_Mode  mode;
    SoftTimer_State state;
} SoftTimer;

typedef SoftTimer SoftTimer;

// void SoftTimer_SetMillisSource(unsigned (*funcSource)());

/**
 * @brief  Проверить срабатывание таймера
 * @param  timer: Дескриптор таймера
 * @return true - таймер сработал, false таймер не сработал или выключен
 */
bool SoftTimer_Occur(SoftTimer *timer);

/**
 * @brief  Инициализация таймера
 * @param  timer:  Дескриптор таймера
 * @param  mode:   Режим работы таймера - SoftTimer_Mode
 * @param  period: Период срабатывания таймера, или таймаут для режима elapsed
 */
void SoftTimer_Init(SoftTimer *timer, SoftTimer_Mode mode, unsigned period);

/**
 * @brief  Получить режим таймера
 * @param  timer: Дескриптор таймера
 * @return Режим таймера
 */
SoftTimer_Mode SoftTimer_GetMode(const SoftTimer *timer);

/**
 * @brief  Получить состояние таймера
 * @param  timer: Дескриптор таймера
 * @return Состояние таймера:
 *           - SoftTimer_StateStop - Таймер остановлен
 *           - SoftTimer_StateRun - Таймер запущен
 *           - SoftTimer_StateElapsedComplete - Таймер завершен в режим elapsed
 */
SoftTimer_State SoftTimer_GetState(const SoftTimer *timer);

/**
 * @brief  Запустить таймер
 * @param  timer: Дескриптор таймера
 */
void SoftTimer_Start(SoftTimer *timer);

/**
 * @brief  Остановить таймер
 * @param  timer: Дескриптор таймера
 */
void SoftTimer_Stop(SoftTimer *timer);

/**
 * @brief  Установить период или таймаут таймера
 * @param  timer:  Дескриптор таймера
 * @param  period: Период или таймаут таймера
 */
void SoftTimer_SetPeriod(SoftTimer *timer, unsigned period);

/**
 * @brief  Получить период или таймаут таймера
 * @param  timer: Дескриптор таймера
 * @return Период или таймаут таймера
 */
unsigned SoftTimer_GetPeriod(const SoftTimer *timer);

#ifdef __cplusplus
}
#endif
