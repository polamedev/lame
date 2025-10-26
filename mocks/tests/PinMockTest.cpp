#include <lame/mocks/PinMock.hpp>

#include <CppUTest/TestHarness.h>

#include <CppUTestExt/MockSupport.h>

TEST_GROUP(EventTests)
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

TEST(EventTests, memoryLeak)
{
    CHECK_TRUE(pin);
}

TEST(EventTests, exceptReadHight)
{
    PinMock_ExceptRead(pin, Pin_State_Hight);
    Pin_State state = Pin_Read(pin);
    CHECK_TRUE(state == Pin_State_Hight);
}

TEST(EventTests, exceptReadLow)
{
    PinMock_ExceptRead(pin, Pin_State_Low);
    Pin_State state = Pin_Read(pin);
    CHECK_TRUE(state == Pin_State_Low);
}

TEST(EventTests, exceptWrite)
{
    PinMock_ExceptWrite(pin, Pin_State_Low);
    Pin_Write(pin, Pin_State_Low);
}

TEST(EventTests, checkToggle)
{
    PinMock_ExceptWrite(pin, Pin_State_Hight);
    PinMock_ExceptWrite(pin, Pin_State_Low);
    Pin_Toggle(pin);
    Pin_Toggle(pin);
}