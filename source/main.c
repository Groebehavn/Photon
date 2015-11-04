#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "gpio.h"
#include "timer.h"
#include "triled.h"
#include "trileddriver.h"
#include "quantumfifo.h"

void main(){
  TRILED_STATE state_1;
  state_1.u8ColorRatios[TRILED_R] = 255;
  state_1.u8ColorRatios[TRILED_G] = 254;
  state_1.u8ColorRatios[TRILED_B] = 0;
  
  TRILED_STATE state_2;
  state_2.u8ColorRatios[TRILED_R] = 255;
  state_2.u8ColorRatios[TRILED_G] = 255;
  state_2.u8ColorRatios[TRILED_B] = 0;
  
  TRILED_STATE state_3;
  state_3.u8ColorRatios[TRILED_R] = 255;
  state_3.u8ColorRatios[TRILED_G] = 200;
  state_3.u8ColorRatios[TRILED_B] = 0;
  
  SystemInit();
  __enable_interrupt();

  /* USER CODE START */
  
  GPIO_Initialize();
  TIMER_Initialize();
  QUANTUMFIFO_Initialize();
  TRILED_Initialize();
  TIM_Cmd(TIM5,ENABLE);
  
  /*
  TRILEDDRIVER_TurnOffAll();
  TRILEDDRIVER_Toggle(TRILED_RIGHT,TRILED_G);
  TRILEDDRIVER_Toggle(TRILED_RIGHT,TRILED_G);
  TRILEDDRIVER_Toggle(TRILED_RIGHT,TRILED_R);
  TRILEDDRIVER_Toggle(TRILED_RIGHT,TRILED_R);
  TRILEDDRIVER_Toggle(TRILED_RIGHT,TRILED_B);
  TRILEDDRIVER_Toggle(TRILED_RIGHT,TRILED_B);
  */
  TRILED_SetLedState(TRILED_LEFT,state_1);
  TRILED_SetLedState(TRILED_CENTER,state_2);
  TRILED_SetLedState(TRILED_RIGHT,state_3);
  TRILED_EnableModule();
  
  /* USER CODE END */
  
  while(1);
}