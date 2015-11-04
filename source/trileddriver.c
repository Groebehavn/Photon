#include "stm32f4xx_gpio.h"
#include "gpio.h"
#include "triled.h"
#include "trileddriver.h"

extern volatile TRILED_PROCDESC gTriLedProcess;
extern uint16_t* GPIO_LEDPINS[3];

void TRILEDDRIVER_TurnOffAll()
{
  GPIO_SetBits(RGBLED_GPIO_PORT,RGBLED_GPIO_ALLPINS);
}

inline void TRILEDDRIVER_TurnOn(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  GPIO_ResetBits(RGBLED_GPIO_PORT,GPIO_LEDPINS[descriptor][color]);
}

inline void TRILEDDRIVER_TurnOff(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  GPIO_SetBits(RGBLED_GPIO_PORT,GPIO_LEDPINS[descriptor][color]);
}

inline void TRILEDDRIVER_Toggle(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color)
{
  GPIO_ToggleBits(RGBLED_GPIO_PORT,GPIO_LEDPINS[descriptor][color]);
}

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
    else{
      TRILEDDRIVER_TurnOff(descriptor,color);
    }
  }
}