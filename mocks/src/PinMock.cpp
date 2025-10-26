#include "PinMock.hpp"

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

struct LAME_Pin_Impl {
    MockSupport   *mock;
    LAME_Pin_State currentState;
};

extern "C" {

void LAME_Pin_Write(LAME_Pin self, LAME_Pin_State state)
{
    self->mock->actualCall("LAME_Pin_Write").withIntParameter("state", state);
    self->currentState = state;
}

LAME_Pin_State LAME_Pin_Read(const LAME_Pin self)
{
    self->mock->actualCall("LAME_Pin_Read");
    return (LAME_Pin_State)self->mock->returnValue().getIntValue();
}

void LAME_Pin_Toggle(LAME_Pin self)
{
    LAME_Pin_Write(self, self->currentState == LAME_Pin_State_Hight ? LAME_Pin_State_Low : LAME_Pin_State_Hight);
}
}

LAME_Pin LAME_PinMock_create(const char *mockName)
{
    LAME_Pin pin = (LAME_Pin)calloc(1, sizeof(LAME_Pin_Impl));
    pin->mock    = &mock(mockName);
    return pin;
}

void LAME_PinMock_destroy(LAME_Pin self)
{
    free(self);
}

void LAME_PinMock_ExceptRead(LAME_Pin self, LAME_Pin_State state, int amount)
{
    self->mock->expectNCalls(amount, "LAME_Pin_Read").andReturnValue((int)state);
}

void LAME_PinMock_ExceptWrite(LAME_Pin self, LAME_Pin_State state, int amount)
{
    self->mock->expectNCalls(amount, "LAME_Pin_Write").withIntParameter("state", state);
}
