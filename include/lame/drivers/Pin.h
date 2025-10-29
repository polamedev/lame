#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct Pin_Impl *Pin;

bool Pin_Read(const Pin handle);
void Pin_Write(Pin handle, bool state);
void Pin_Toggle(Pin handle);

#ifdef __cplusplus
}
#endif
