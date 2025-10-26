#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum Pin_State {
    Pin_State_Hight,
    Pin_State_Low
} Pin_State;

typedef struct Pin_Impl *Pin;

Pin_State Pin_Read(const Pin handle);
void      Pin_Write(Pin handle, Pin_State state);
void      Pin_Toggle(Pin handle);

#ifdef __cplusplus
}
#endif
