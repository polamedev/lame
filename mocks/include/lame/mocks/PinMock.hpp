#include <lame/drivers/Pin.h>

LAME_Pin LAME_PinMock_create(const char *mockName);
void     LAME_PinMock_destroy(LAME_Pin);
void     LAME_PinMock_ExceptRead(LAME_Pin self, LAME_Pin_State tate, int amount = 1);
void     LAME_PinMock_ExceptWrite(LAME_Pin self, LAME_Pin_State state, int amount = 1);
