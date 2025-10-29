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
    PinMock_ExceptRead(pin, Pin_State_Hight);
    Pin_State state = Pin_Read(pin);
    CHECK_TRUE(state == Pin_State_Hight);
}

TEST(PinMock, exceptReadLow)
{
    PinMock_ExceptRead(pin, Pin_State_Low);
    Pin_State state = Pin_Read(pin);
    CHECK_TRUE(state == Pin_State_Low);
}

TEST(PinMock, exceptWrite)
{
    PinMock_ExceptWrite(pin, Pin_State_Low);
    Pin_Write(pin, Pin_State_Low);
}

TEST(PinMock, checkToggle)
{
    PinMock_ExceptWrite(pin, Pin_State_Hight);
    PinMock_ExceptWrite(pin, Pin_State_Low);
    Pin_Toggle(pin);
    Pin_Toggle(pin);
}
