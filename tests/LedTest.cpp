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

unsigned blinkPeriod = 150;

#define CHECK_PIN(expected)                    \
    do {                                       \
        CHECK_TRUE(Pin_Read(pin) == expected); \
    } while (0)

/**
 * @brief  Проверка текущего состояния пина и увеличение текущего времени
 */
#define PROCESS_STAGE_BLINK(expected_pin_state) \
    do {                                        \
        Led_Task();                             \
        CHECK_PIN(expected_pin_state);          \
        millis_set(millis() + blinkPeriod);     \
    } while (0)

/**
 * @brief  Проверка одного блинка
 */
#define CHECK_BLINK()               \
    do {                            \
        PROCESS_STAGE_BLINK(true);  \
        PROCESS_STAGE_BLINK(false); \
    } while (0)

/**
 * @brief  Проверка последнего блинка с увеличенной задержкой
 */
#define CHECK_DELAYED_BLINK()           \
    do {                                \
        PROCESS_STAGE_BLINK(true);      \
        for (int i = 0; i < 5; i++) {   \
            PROCESS_STAGE_BLINK(false); \
        }                               \
    } while (0)

/**
 * @brief  Проверка полного цикла блинка с короткими паузками и длинными
 */
#define CHECK_BLINK_FULL_CYCLE(blinkCount)             \
    do {                                               \
        if (blinkCount > 1) {                          \
            for (int i = 0; i < blinkCount - 1; i++) { \
                CHECK_BLINK();                         \
            }                                          \
        }                                              \
        CHECK_DELAYED_BLINK();                         \
    } while (0)

TEST_GROUP(LedTests) {
Led led;
Pin pin;

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
    CHECK_PIN(false);

    Led_Destroy(led);
    PinMock_destroy(pin);
}

TEST(LedTests, turnOnLed)
{
    Led_Write(led, true);
    CHECK_PIN(true);
}

TEST(LedTests, turnOffLed)
{
    Led_Write(led, true);
    Led_Write(led, false);
    CHECK_PIN(false);
}

TEST(LedTests, toggle)
{
    Led_Toggle(led);
    CHECK_PIN(true);
    Led_Toggle(led);
    CHECK_PIN(false);
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
    CHECK_PIN(false);
}

TEST(LowActiveLedTests, turnOffLed)
{
    Led_Write(led, true);
    Led_Write(led, false);
    CHECK_PIN(true);
}

// ####################################################################

TEST_GROUP(BlinkLedTests) {

Led led;
Pin pin;

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

}; // TEST_GROUP(BlinkLedTests)

TEST(BlinkLedTests, blink1_cycle)
{
    CHECK_BLINK_FULL_CYCLE(1);
}

TEST(BlinkLedTests, blink2_cycle)
{
    Led_SetBlinkCount(led, 2);
    CHECK_BLINK_FULL_CYCLE(2);
}

TEST(BlinkLedTests, blink1_fewCycle)
{
    Led_SetBlinkCount(led, 1);
    CHECK_BLINK_FULL_CYCLE(1);
    CHECK_BLINK_FULL_CYCLE(1);
    CHECK_BLINK_FULL_CYCLE(1);
}

TEST(BlinkLedTests, blink2_fewCycle)
{
    Led_SetBlinkCount(led, 2);
    CHECK_BLINK_FULL_CYCLE(2);
    CHECK_BLINK_FULL_CYCLE(2);
    CHECK_BLINK_FULL_CYCLE(2);
}

TEST(BlinkLedTests, blink3_fewCycle)
{
    Led_SetBlinkCount(led, 3);
    CHECK_BLINK_FULL_CYCLE(3);
    CHECK_BLINK_FULL_CYCLE(3);
    CHECK_BLINK_FULL_CYCLE(3);
}

TEST(BlinkLedTests, detailed_blink2)
{
    Led_SetBlinkCount(led, 2);

    // Первый цикл
    CHECK_BLINK();
    CHECK_DELAYED_BLINK();

    // Второй цикл
    CHECK_BLINK();
    CHECK_DELAYED_BLINK();
    // Третий цикл
    CHECK_BLINK();
}

TEST(BlinkLedTests, stop_blink)
{
    Led_SetBlinkCount(led, 3);
    unsigned msec = 0;
    millis_set(msec);
    Led_Task();
    CHECK_PIN(true);
    Led_StopBlink(led);
    CHECK_PIN(false);
}

TEST(BlinkLedTests, reset_after_change_blink_count)
{
    Led_SetBlinkCount(led, 3);
    CHECK_PIN(true);

    unsigned msec = 0;
    millis_set(msec);

    CHECK_BLINK();
    PROCESS_STAGE_BLINK(true);

    Led_SetBlinkCount(led, 1);
    CHECK_DELAYED_BLINK();
    CHECK_DELAYED_BLINK();
}

// TODO Дописать тесты
