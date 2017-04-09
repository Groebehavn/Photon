#ifndef _TRILED_H_
#define _TRILED_H_

typedef __packed struct t_sTRILED_STATE
{
  U8 u8ColorRatios[3];
}TRILED_STATE;

typedef struct t_sTRILED_PROCDESC
{
  bool bEnabled;
  bool abEnabledLeds[3];
  bool abActiveLeds[3][3];
  TRILED_STATE aLedStates[3];
  U8 u8Progress;
  U8 u8SynchronizedProgress;
  U8 u8ProgressMargin;
  U8 u8MaxProgressMargin;
}TRILED_PROCDESC;

void TRILED_SetLedState(TRILED_DESCRIPTOR descriptor, TRILED_STATE state);
TRILED_STATE TRILED_GetLedState(TRILED_DESCRIPTOR descriptor);
void TRILED_TurnOffAll();
void TRILED_TurnOn(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color);
void TRILED_TurnOff(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color);
void TRILED_Toggle(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color);
void TRILED_IncrementProgress();
void TRILED_Initialize(void);
void TRILED_EnableModule(void);
void TRILED_DisableModule(void);
void TRILED_Tick();

#endif