#include <lame/device/Led.h>

#include <lame/mocks/PinMock.hpp>

#include <CppUTest/TestHarness.h>

/*
Список тестов диода

Что библиотека должна делать:
I.  Прямой режим светодиода
    1.  Управлять уровнем диода на линии - в зависимости от полярности включения.
        Подавать высокое напряжение для включения при прямом подключении диода
        Низкое напряжение при обратном подключении
    2.+ После Инициализации должен диод должен быть выключен
    3.  Читать состояние светодиода
    3.  Использовании функции toggle
II. Режим мигания диода.
    1.  Не должен мигать, если светодиод не запущен
    2.  Мигать один раз, через равные промежутки времени
    3.  Мигать несколько раз. Между быстрыми миганиями короткий период, Через группы миганий большой период
III. Дополнительные механизмы
    1.  Проверка утечки памяти
    2.  Проверка конструктора и деструктора
*/

TEST_GROUP(LedTests) {
Led led;
Pin pin;

void setup()
{
    pin = PinMock_create("led", true);
    led = Led_Create(pin, false, 0);
}

void teardown()
{
    PinMock_destroy(pin);
}
}; // TEST_GROUP(LedTests)

TEST(LedTests, clearAfterCreate)
{
    Pin pin = PinMock_create("", true);

    Pin_Write(pin, Pin_State_Hight);

    Led led = Led_Create(pin, false, 0);
    CHECK_TRUE(Pin_Read(pin) == Pin_State_Low);

    PinMock_destroy(pin);
}

TEST(LedTests, turnOnLed)
{
    Led_SetActive(led, true);
    CHECK_TRUE(Pin_Read(pin) == Pin_State_Hight);
}

TEST(LedTests, turnOffLed)
{
    Led_SetActive(led, true);
    Led_SetActive(led, false);
    CHECK_TRUE(Pin_Read(pin) == Pin_State_Low);
}

TEST(LedTests, toggle)
{
    Led_Toggle(led);
    CHECK_TRUE(Pin_Read(pin) == Pin_State_Hight);
    Led_Toggle(led);
    CHECK_TRUE(Pin_Read(pin) == Pin_State_Low);
}



// TODO Дописать тесты
