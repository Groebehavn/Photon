#include "headers.h"

static TRILED_PROCDESC gTriLedProcess;

static inline void SynchronizeProgress()
{
  gTriLedProcess.u8SynchronizedProgress = gTriLedProcess.u8Progress;
}

static inline void SaveAndResetMarginCounter()
{
  if(gTriLedProcess.u8ProgressMargin > gTriLedProcess.u8MaxProgressMargin)
  {
    gTriLedProcess.u8MaxProgressMargin = gTriLedProcess.u8ProgressMargin;
  }
}

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
  gTriLedProcess.u8SynchronizedProgress = 0;
  gTriLedProcess.u8ProgressMargin = 0;
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
  TRILED_TurnOffAll();
  gTriLedProcess.bEnabled = false;
  gTriLedProcess.abEnabledLeds[TRILED_LEFT] = false;
  gTriLedProcess.abEnabledLeds[TRILED_CENTER] = false;
  gTriLedProcess.abEnabledLeds[TRILED_RIGHT] = false;
}

/**
  *     Worst case 11 ticks (+2 asserts) long takes to return from this function
  */
static inline void TRILED_ProgressSpecificLedHandler(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  U8 u8LocalProgress = gTriLedProcess.u8Progress;
  if(gTriLedProcess.abEnabledLeds[descriptor])
  {
    if(gTriLedProcess.aLedStates[descriptor].u8ColorRatios[color]
       >
       u8LocalProgress)
    {
      TRILED_TurnOn(descriptor,color);
    }
    else
    {
      TRILED_TurnOff(descriptor,color);
    }
  }
}

void TRILED_TurnOffAll()
{
  //TODO: ez memset, 9*sizeof(bool)
  //TODO: ez most akkor jó?
  memset((void*)&gTriLedProcess.abActiveLeds, 0, 9*sizeof(bool));
  TRILEDDRIVER_TurnOffAll();
}

inline void TRILED_TurnOn(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  if(gTriLedProcess.abActiveLeds[descriptor][color])
  {
    return;
  }
  gTriLedProcess.abActiveLeds[descriptor][color] = true;
  TRILEDDRIVER_TurnOn(descriptor,color);
}

inline void TRILED_TurnOff(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  if(!gTriLedProcess.abActiveLeds[descriptor][color])
  {
    return;
  }
  gTriLedProcess.abActiveLeds[descriptor][color] = false;
  TRILEDDRIVER_TurnOff(descriptor,color);
}

inline void TRILED_Toggle(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  gTriLedProcess.abActiveLeds[descriptor][color] = !gTriLedProcess.abActiveLeds[descriptor][color];
  TRILEDDRIVER_Toggle(descriptor,color);
}

void TRILED_IncrementProgress()
{
  gTriLedProcess.u8Progress++;
}

void TRILED_Tick()
{
  U8 u8Sync = gTriLedProcess.u8SynchronizedProgress;
  if(gTriLedProcess.u8Progress != u8Sync)
  {
    SynchronizeProgress();
    if(gTriLedProcess.bEnabled == true)
    {
      TRILED_ProgressSpecificLedHandler(TRILED_LEFT,TRILED_R);
      TRILED_ProgressSpecificLedHandler(TRILED_LEFT,TRILED_G);
      TRILED_ProgressSpecificLedHandler(TRILED_LEFT,TRILED_B);
      
      TRILED_ProgressSpecificLedHandler(TRILED_CENTER,TRILED_R);
      TRILED_ProgressSpecificLedHandler(TRILED_CENTER,TRILED_G);
      TRILED_ProgressSpecificLedHandler(TRILED_CENTER,TRILED_B);
      
      TRILED_ProgressSpecificLedHandler(TRILED_RIGHT,TRILED_R);
      TRILED_ProgressSpecificLedHandler(TRILED_RIGHT,TRILED_G);
      TRILED_ProgressSpecificLedHandler(TRILED_RIGHT,TRILED_B);
    }
    
    SaveAndResetMarginCounter();
  }
  else
  {
    gTriLedProcess.u8ProgressMargin++;
  }
}