#ifndef _TRILED_H_
#define _TRILED_H_

#include "systypes.h"

typedef enum t_TRILED_DESCRIPTOR
{
  TRILED_LEFT = 0,
  TRILED_CENTER = 1,
  TRILED_RIGHT = 2
}TRILED_DESCRIPTOR;

typedef enum t_TRILED_COLOR
{
  TRILED_R = 0,
  TRILED_G = 1,
  TRILED_B = 2
}TRILED_COLOR;

typedef __packed struct t_sTRILED_STATE
{
  U8 u8ColorRatios[3];
}TRILED_STATE;

typedef __packed struct t_sTRILED_PROCDESC
{
  bool bEnabled;
  bool abEnabledLeds[3];
  TRILED_STATE aLedStates[3];
  U8 u8Progress;
}TRILED_PROCDESC;

void TRILED_SetLedState(TRILED_DESCRIPTOR descriptor, TRILED_STATE state);
TRILED_STATE TRILED_GetLedState(TRILED_DESCRIPTOR descriptor);
void TRILED_Initialize(void);
void TRILED_EnableModule(void);
void TRILED_DisableModule(void);

#endif