#include "stm32f4xx_gpio.h"
#include "gpio.h"
#include "triled.h"
#include "trileddriver.h"

extern volatile TRILED_PROCDESC gTriLedProcess;
extern uint16_t* GPIO_LEDPINS[3];

void TRILEDDRIVER_TurnOffAll()
{
  U8 u8i, u8j;
  
  for(u8i = 0; u8i < 3; u8i++)
  {
    for(u8j = 0; u8j < 3; u8j++)
    {
      gTriLedProcess.abActiveLeds[u8i][u8j] = false;
    }
  }
  
  GPIO_SetBits(RGBLED_GPIO_PORT,RGBLED_GPIO_ALLPINS);
}

inline void TRILEDDRIVER_TurnOn(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  if(gTriLedProcess.abActiveLeds[descriptor][color])
  {
    return;
  }
  gTriLedProcess.abActiveLeds[descriptor][color] = true;
  GPIO_ResetBits(RGBLED_GPIO_PORT,GPIO_LEDPINS[descriptor][color]);
}

inline void TRILEDDRIVER_TurnOff(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  if(!gTriLedProcess.abActiveLeds[descriptor][color])
  {
    return;
  }
  gTriLedProcess.abActiveLeds[descriptor][color] = false;
  GPIO_SetBits(RGBLED_GPIO_PORT,GPIO_LEDPINS[descriptor][color]);
}

inline void TRILEDDRIVER_Toggle(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  gTriLedProcess.abActiveLeds[descriptor][color] = !gTriLedProcess.abActiveLeds[descriptor][color];
  GPIO_ToggleBits(RGBLED_GPIO_PORT,GPIO_LEDPINS[descriptor][color]);
}

/**
  *     Worst case 11 ticks (+2 asserts) long takes to return from this function
  */
void TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  U8 u8LocalProgress = gTriLedProcess.u8Progress;
  if(gTriLedProcess.abEnabledLeds[descriptor])
  {
    if(gTriLedProcess.aLedStates[descriptor].u8ColorRatios[color]
       >
       u8LocalProgress)
    {
      TRILEDDRIVER_TurnOn(descriptor,color);
    }
    else
    {
      TRILEDDRIVER_TurnOff(descriptor,color);
    }
  }
}