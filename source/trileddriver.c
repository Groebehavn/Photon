#include "headers.h"

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