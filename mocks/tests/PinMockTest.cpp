#include <lame/PinMock.hpp>

#include <CppUTest/TestHarness.h>

#include <CppUTestExt/MockSupport.h>

TEST_GROUP(EventTests)
{

    LAME_Pin pin;

    void setup()
    {
        pin = LAME_PinMock_create("led");
    }

    void teardown()
    {
        LAME_PinMock_destroy(pin);
        mock("led").checkExpectations();
    }
};

TEST(EventTests, memoryLeak)
{
    CHECK_TRUE(pin);
}

TEST(EventTests, exceptReadHight)
{
    LAME_PinMock_ExceptRead(pin, LAME_Pin_State_Hight);
    LAME_Pin_State state = LAME_Pin_Read(pin);
    CHECK_TRUE(state == LAME_Pin_State_Hight);
}

TEST(EventTests, exceptReadLow)
{
    LAME_PinMock_ExceptRead(pin, LAME_Pin_State_Low);
    LAME_Pin_State state = LAME_Pin_Read(pin);
    CHECK_TRUE(state == LAME_Pin_State_Low);
}

TEST(EventTests, exceptWrite)
{
    LAME_PinMock_ExceptWrite(pin, LAME_Pin_State_Low);
    LAME_Pin_Write(pin, LAME_Pin_State_Low);
}

TEST(EventTests, checkToggle)
{
    LAME_PinMock_ExceptWrite(pin, LAME_Pin_State_Hight);
    LAME_PinMock_ExceptWrite(pin, LAME_Pin_State_Low);
    LAME_Pin_Toggle(pin);
    LAME_Pin_Toggle(pin);
}