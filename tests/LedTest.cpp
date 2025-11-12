#include <lame/device/Led.h>

#include <lame/mocks/PinMock.hpp>
#include <lame/mocks/timeServiceMock.hpp>

#include <CppUTest/TestHarness.h>

/*
Список тестов диода

Что модуль должен делать:
I.  Прямой режим светодиода
    1.+ Управлять уровнем диода на линии - в зависимости от полярности включения.
        Подавать высокое напряжение для включения при прямом подключении диода
        Низкое напряжение при обратном подключении
    2.+ После Инициализации должен диод должен быть выключен
    3.+ Читать состояние светодиода
    3.+ Использовании функции toggle
II. Режим мигания диода.
    1.  Не должен мигать, если светодиод не запущен
    2.  Мигать один раз, через равные промежутки времени
    3.  Мигать несколько раз. Между быстрыми миганиями короткий период, Через группы миганий большой период
III. Дополнительные механизмы
    1.+ Проверка утечки памяти
    2.+ Проверка конструктора и деструктора
*/

#define checkPin(expected)                     \
    do {                                       \
        CHECK_TRUE(Pin_Read(pin) == expected); \
    } while (0)

TEST_GROUP(LedTests) {
Led      led;
Pin      pin;
unsigned blinkPeriod = 150;

void setup()
{
    pin = PinMock_create("led", true);
    led = Led_Create(pin, false);
}

void teardown()
{
    Led_Destroy(led);
    PinMock_destroy(pin);
}
}; // TEST_GROUP(LedTests)

TEST(LedTests, createAndDestroy)
{
    Led led0 = led;
    Led_Destroy(led);
    led = Led_Create(pin, false);
    LONGS_EQUAL(led0, led);
}

TEST(LedTests, clearAfterCreate)
{
    Pin pin = PinMock_create("", true);

    Pin_Write(pin, true);

    Led led = Led_Create(pin, false);
    checkPin(false);

    Led_Destroy(led);
    PinMock_destroy(pin);
}

TEST(LedTests, turnOnLed)
{
    Led_Write(led, true);
    checkPin(true);
}

TEST(LedTests, turnOffLed)
{
    Led_Write(led, true);
    Led_Write(led, false);
    checkPin(false);
}

TEST(LedTests, toggle)
{
    Led_Toggle(led);
    checkPin(true);
    Led_Toggle(led);
    checkPin(false);
}

TEST(LedTests, read)
{
    CHECK_TRUE(Led_Read(led) == false);
    Led_Toggle(led);
    CHECK_TRUE(Led_Read(led) == true);
}

// ################################################################

TEST_GROUP(LowActiveLedTests) {
Led led;
Pin pin;

void setup()
{
    pin = PinMock_create("led", true);
    led = Led_Create(pin, true);
    millis_set(0);
}

void teardown()
{
    Led_Destroy(led);
    PinMock_destroy(pin);
}
}; // TEST_GROUP(LowActiveLedTests)

TEST(LowActiveLedTests, turnOnLed)
{
    Led_Write(led, true);
    checkPin(false);
}

TEST(LowActiveLedTests, turnOffLed)
{
    Led_Write(led, true);
    Led_Write(led, false);
    checkPin(true);
}

// ####################################################################

TEST_GROUP(BlinkLedTests) {

Led      led;
Pin      pin;
unsigned blinkPeriod = 150;

void setup()
{
    pin = PinMock_create("led", true);
    led = Led_Create(pin, false);
    millis_set(0);
    Led_StartBlink(led);
}

void teardown()
{
    Led_Destroy(led);
    PinMock_destroy(pin);
}

// Helpers

void checkBlinkCycleLed(unsigned blinkCount)
{
    unsigned msec = 0;
    char     str[17];
    for (unsigned i = 0; i < blinkCount; i++) {
        sprintf(str, "Cycle %u", i);

        Led_Task();
        CHECK_TRUE_TEXT(Pin_Read(pin) == true, str);
        msec += blinkPeriod;
        millis_set(msec);

        Led_Task();
        CHECK_TRUE_TEXT(Pin_Read(pin) == false, str);
        if (i == blinkCount - 1) {
            msec += 5 * blinkPeriod;
        }
        else {
            msec += blinkPeriod;
        }
        millis_set(msec);
    }
}

/**
 * @brief  Запустить задачу Led_Task() до заданного времени в заданное время и после
 * @param  msec:
 */
void processLedTaskInTime(unsigned msec)
{
    Led_Task();
    if (msec > 0) {
        millis_set(msec - 1);
        Led_Task();
    }
    millis_set(msec);
    Led_Task();
    millis_set(msec + 1);
    Led_Task();
}

/**
 * @brief  Проверяет одну фазу мигания начиная с времени start_ms
 *         Проверяет первую фазу, потом устаналвиает время через период и проверяет вторую фазу
 * @param  exceptBlink:
 * @param  start_ms:
 */
void incrementTimeLed(bool exceptBlink, unsigned start_ms)
{
    processLedTaskInTime(start_ms);
    if (exceptBlink) {
        checkPin(true);
    }
    else {
        checkPin(false);
    }

    processLedTaskInTime(start_ms + blinkPeriod);
    checkPin(false);
}

}; // TEST_GROUP(BlinkLedTests)

TEST(BlinkLedTests, blink1_cycle)
{
    checkBlinkCycleLed(1);
}

TEST(BlinkLedTests, blink2_cycle)
{
    Led_SetBlinkCount(led, 2);
    checkBlinkCycleLed(2);
}

TEST(BlinkLedTests, blink1_fewCycle)
{
    Led_SetBlinkCount(led, 1);
    checkBlinkCycleLed(1);
    checkBlinkCycleLed(1);
    checkBlinkCycleLed(1);
}

TEST(BlinkLedTests, blink2_fewCycle)
{
    Led_SetBlinkCount(led, 2);
    checkBlinkCycleLed(2);
    checkBlinkCycleLed(2);
    checkBlinkCycleLed(2);
}

TEST(BlinkLedTests, blink3_fewCycle)
{
    Led_SetBlinkCount(led, 3);
    checkBlinkCycleLed(3);
    checkBlinkCycleLed(3);
    checkBlinkCycleLed(3);
}

TEST(BlinkLedTests, detailed_blink2)
{
    Led_SetBlinkCount(led, 2);

    unsigned ms = 0;
    // Первый цикл
    incrementTimeLed(true, ms);
    incrementTimeLed(true, ms += 2 * blinkPeriod);
    incrementTimeLed(false, ms += 2 * blinkPeriod);
    incrementTimeLed(false, ms += 2 * blinkPeriod);

    // Второй цикл
    incrementTimeLed(true, ms += 2 * blinkPeriod);
    incrementTimeLed(true, ms += 2 * blinkPeriod);
    incrementTimeLed(false, ms += 2 * blinkPeriod);
    incrementTimeLed(false, ms += 2 * blinkPeriod);

    incrementTimeLed(true, ms += 2 * blinkPeriod);
}

#define PROCESS_STAGE_BLINK(expected_pin_state) \
    do {                                        \
        Led_Task();                             \
        checkPin(expected_pin_state);           \
        millis_set(millis() + blinkPeriod);     \
    } while (0)

#define PROCESS_DELAY_STAGE_BLINK() \
    do {                            \
        PROCESS_STAGE_BLINK(false); \
        PROCESS_STAGE_BLINK(false); \
        PROCESS_STAGE_BLINK(false); \
        PROCESS_STAGE_BLINK(false); \
        PROCESS_STAGE_BLINK(false); \
    } while (0)

TEST(BlinkLedTests, stop_blink)
{
    Led_SetBlinkCount(led, 3);
    unsigned msec = 0;
    millis_set(msec);
    Led_Task();
    checkPin(true);
    Led_StopBlink(led);
    checkPin(false);
}

TEST(BlinkLedTests, reset_after_change_blink_count)
{
    Led_SetBlinkCount(led, 3);
    checkPin(true);

    unsigned msec = 0;
    millis_set(msec);

    PROCESS_STAGE_BLINK(true);
    PROCESS_STAGE_BLINK(false);
    PROCESS_STAGE_BLINK(true);

    Led_SetBlinkCount(led, 1);
    PROCESS_STAGE_BLINK(true);
    PROCESS_DELAY_STAGE_BLINK();
    PROCESS_STAGE_BLINK(true);
    PROCESS_DELAY_STAGE_BLINK();
}

// TODO Дописать тесты
