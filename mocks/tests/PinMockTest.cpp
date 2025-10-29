#include <lame/mocks/PinMock.hpp>

#include <CppUTest/TestHarness.h>

#include <CppUTestExt/MockSupport.h>

/**
 * Режим мока - режим когда объект четко отслеживает вызовы
 * 
 * Режим шпиона - Режим когда объект просто сохраняет в себя записанное состояние и может его вернуть
 * Функционал - 
 */

TEST_GROUP(PinMock)
{

    Pin pin;

    void setup()
    {
        pin = PinMock_create("led");
    }

    void teardown()
    {
        PinMock_destroy(pin);
        mock("led").checkExpectations();
    }
};

TEST(PinMock, memoryLeak)
{
    CHECK_TRUE(pin);
}

TEST(PinMock, exceptReadHight)
{
    PinMock_ExceptRead(pin, true);
    bool state = Pin_Read(pin);
    CHECK_TRUE(state == true);
}

TEST(PinMock, exceptReadLow)
{
    PinMock_ExceptRead(pin, false);
    bool state = Pin_Read(pin);
    CHECK_TRUE(state == false);
}

TEST(PinMock, exceptWrite)
{
    PinMock_ExceptWrite(pin, false);
    Pin_Write(pin, false);
}

TEST(PinMock, checkToggle)
{
    PinMock_ExceptWrite(pin, true);
    PinMock_ExceptWrite(pin, false);
    Pin_Toggle(pin);
    Pin_Toggle(pin);
}
