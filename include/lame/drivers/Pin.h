#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum LAME_Pin_State {
    LAME_Pin_State_Hight,
    LAME_Pin_State_Low
} LAME_Pin_State;

typedef struct LAME_Pin_Impl *LAME_Pin;

LAME_Pin_State LAME_Pin_Read(const LAME_Pin handle);
void           LAME_Pin_Write(LAME_Pin handle, LAME_Pin_State state);
void           LAME_Pin_Toggle(LAME_Pin handle);

#ifdef __cplusplus
}
#endif
