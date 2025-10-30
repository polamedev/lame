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

// Helpers

void checkBlinkCycleLed(unsigned blinkCount)
{
    unsigned msec = 0;
    char     str[10];
    for (unsigned i = 0; i < blinkCount; i++) {
        sprintf(str, "Cycle %i", i);

        Led_Task();
        CHECK_TRUE_TEXT(Pin_Read(pin) == true, str);
        msec += 100;
        millis_set(msec);

        Led_Task();
        CHECK_TRUE_TEXT(Pin_Read(pin) == false, str);
        if (i == blinkCount - 1) {
            msec += 500;
        }
        else {
            msec += 100;
        }
        millis_set(msec);
    }
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

void startLedTaskInTime(unsigned msec)
{
    millis_set(msec);
    Led_Task();
}

TEST(BlinkLedTests, detailed_blink2)
{
    Led_SetBlinkCount(led, 2);

    startLedTaskInTime(0);
    checkPin(true);
    startLedTaskInTime(100);
    checkPin(false);

    startLedTaskInTime(200);
    checkPin(true);
    startLedTaskInTime(300);
    checkPin(false);

    startLedTaskInTime(400);
    checkPin(false);
    startLedTaskInTime(500);
    checkPin(false);

    startLedTaskInTime(600);
    checkPin(false);
    startLedTaskInTime(700);
    checkPin(false);


    startLedTaskInTime(800);
    checkPin(true);
    startLedTaskInTime(900);
    checkPin(false);

    startLedTaskInTime(1000);
    checkPin(true);
    startLedTaskInTime(1100);
    checkPin(false);

    startLedTaskInTime(1200);
    checkPin(false);
    startLedTaskInTime(1300);
    checkPin(false);

    startLedTaskInTime(1400);
    checkPin(false);
    startLedTaskInTime(1500);
    checkPin(false);

    startLedTaskInTime(1600);
    checkPin(true);
}

// TODO Дописать тесты
