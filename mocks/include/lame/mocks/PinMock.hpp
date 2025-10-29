#include <lame/drivers/Pin.h>

/**
 * @brief  Создать мок объект пина
 * @param  mockName: Имя мока
 * @param  isSpy: Режим шпиона - режим в котором объект не будет отслеживать конкретные вызовы, 
 *                а будет просто сохранять свое состояни
 * @return Pin - 
 */
Pin  PinMock_create(const char *mockName, bool isSpy = false);
void PinMock_destroy(Pin);
void PinMock_ExceptRead(Pin self, bool state, int amount = 1);
void PinMock_ExceptWrite(Pin self, bool state, int amount = 1);
