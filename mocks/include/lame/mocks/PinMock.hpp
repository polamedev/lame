#include <lame/drivers/Pin.h>

Pin  PinMock_create(const char *mockName);
void PinMock_destroy(Pin);
void PinMock_ExceptRead(Pin self, Pin_State tate, int amount = 1);
void PinMock_ExceptWrite(Pin self, Pin_State state, int amount = 1);
