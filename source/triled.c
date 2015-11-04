#include "triled.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "gpio.h"

volatile TRILED_PROCDESC gTriLedProcess;

void TRILED_SetLedState(TRILED_DESCRIPTOR descriptor, TRILED_STATE state)
{
  gTriLedProcess.aLedStates[descriptor] = state;
}

TRILED_STATE TRILED_GetLedState(TRILED_DESCRIPTOR descriptor)
{
  return gTriLedProcess.aLedStates[descriptor];
}

void TRILED_Initialize()
{
  TRILED_DisableModule();
  gTriLedProcess.u8Progress = 0;
}

void TRILED_EnableModule()
{
  gTriLedProcess.bEnabled = true;
  gTriLedProcess.abEnabledLeds[TRILED_R] = true;
  gTriLedProcess.abEnabledLeds[TRILED_G] = true;
  gTriLedProcess.abEnabledLeds[TRILED_B] = true;
  TIM_Cmd(TIM4,ENABLE);
}

void TRILED_DisableModule()
{
  TIM_Cmd(TIM4,DISABLE);
  TRILEDDRIVER_TurnOffAll();
  gTriLedProcess.bEnabled = false;
  gTriLedProcess.abEnabledLeds[TRILED_LEFT] = false;
  gTriLedProcess.abEnabledLeds[TRILED_CENTER] = false;
  gTriLedProcess.abEnabledLeds[TRILED_RIGHT] = false;
}