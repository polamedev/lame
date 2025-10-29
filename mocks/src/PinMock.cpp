#include "PinMock.hpp"

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

struct Pin_Impl {
    MockSupport *mock;
    bool    currentState;
    bool         isSpy;
};

extern "C" {

void Pin_Write(Pin self, bool state)
{
    if (!self->isSpy) {
        self->mock->actualCall("Pin_Write").withIntParameter("state", state);
    }
    self->currentState = state;
}

bool Pin_Read(const Pin self)
{
    if (self->isSpy) {
        return self->currentState;
    }
    else {
        self->mock->actualCall("Pin_Read");
        return (bool)self->mock->returnValue().getIntValue();
    }
}

void Pin_Toggle(Pin self)
{
    Pin_Write(self, self->currentState == true ? false : true);
}
}

Pin PinMock_create(const char *mockName, bool isSpy)
{
    Pin pin    = (Pin)calloc(1, sizeof(Pin_Impl));
    pin->isSpy = isSpy;
    pin->mock  = &mock(mockName);
    return pin;
}

void PinMock_destroy(Pin self)
{
    free(self);
}

void PinMock_ExceptRead(Pin self, bool state, int amount)
{
    self->mock->expectNCalls(amount, "Pin_Read").andReturnValue((int)state);
}

void PinMock_ExceptWrite(Pin self, bool state, int amount)
{
    self->mock->expectNCalls(amount, "Pin_Write").withIntParameter("state", state);
}
