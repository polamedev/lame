#include <lame/mocks/PinMock.hpp>

#include <CppUTest/TestHarness.h>

#include <CppUTestExt/MockSupport.h>

/**
 * Режим мока - режим когда объект четко отслеживает вызовы
 *
 * Режим шпиона - Режим когда объект просто сохраняет в себя записанное состояние и может его вернуть
 * Функционал -
 */

TEST_GROUP(PinMockSpy) {
Pin pin;

void setup()
{
    pin = PinMock_create("led", true);
}

void teardown()
{
    PinMock_destroy(pin);
    mock("led").checkExpectations();
}
}; // TEST_GROUP(PinMockSpy)

TEST(PinMockSpy, readPinAfterCreate)
{
    CHECK_TRUE(Pin_Read(pin) == false);
}

TEST(PinMockSpy, writeLowPin)
{
    Pin_Write(pin, false);
    CHECK_TRUE(Pin_Read(pin) == false);
}

TEST(PinMockSpy, writeHightPin)
{
    Pin_Write(pin, true);
    CHECK_TRUE(Pin_Read(pin) == true);
}

TEST(PinMockSpy, toggle)
{
    Pin_Toggle(pin);
    CHECK_TRUE(Pin_Read(pin) == true);
    Pin_Toggle(pin);
    CHECK_TRUE(Pin_Read(pin) == false);
}
