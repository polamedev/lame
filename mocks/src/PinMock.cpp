#include "PinMock.hpp"

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

struct Pin_Impl {
    MockSupport *mock;
    Pin_State    currentState;
};

extern "C" {

void Pin_Write(Pin self, Pin_State state)
{
    self->mock->actualCall("Pin_Write").withIntParameter("state", state);
    self->currentState = state;
}

Pin_State Pin_Read(const Pin self)
{
    self->mock->actualCall("Pin_Read");
    return (Pin_State)self->mock->returnValue().getIntValue();
}

void Pin_Toggle(Pin self)
{
    Pin_Write(self, self->currentState == Pin_State_Hight ? Pin_State_Low : Pin_State_Hight);
}
}

Pin PinMock_create(const char *mockName)
{
    Pin pin   = (Pin)calloc(1, sizeof(Pin_Impl));
    pin->mock = &mock(mockName);
    return pin;
}

void PinMock_destroy(Pin self)
{
    free(self);
}

void PinMock_ExceptRead(Pin self, Pin_State state, int amount)
{
    self->mock->expectNCalls(amount, "Pin_Read").andReturnValue((int)state);
}

void PinMock_ExceptWrite(Pin self, Pin_State state, int amount)
{
    self->mock->expectNCalls(amount, "Pin_Write").withIntParameter("state", state);
}
