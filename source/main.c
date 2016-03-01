#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "gpio.h"
#include "timer.h"
#include "triled.h"
#include "trileddriver.h"
#include "quantumfifo.h"
#include "quantumserver.h"

void main(){
  /*
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
  */
  QUANTUM quantumbase;
  quantumbase.u16Properties = 0x0003;
  quantumbase.ledState[0].u8ColorRatios[TRILED_R] = 0;
  quantumbase.ledState[0].u8ColorRatios[TRILED_G] = 0;
  quantumbase.ledState[0].u8ColorRatios[TRILED_B] = 0;
  quantumbase.ledState[1].u8ColorRatios[TRILED_R] = 0;
  quantumbase.ledState[1].u8ColorRatios[TRILED_G] = 0;
  quantumbase.ledState[1].u8ColorRatios[TRILED_B] = 0;
  quantumbase.ledState[2].u8ColorRatios[TRILED_R] = 0;
  quantumbase.ledState[2].u8ColorRatios[TRILED_G] = 0;
  quantumbase.ledState[2].u8ColorRatios[TRILED_B] = 0;
  
  
  SystemInit();
  __enable_interrupt();

  /* USER CODE START */
  
  GPIO_Initialize();
  TIMER_Initialize();
  TRILED_Initialize();
  QUANTUMSERVER_Initialize();
  
  for(int j=0; j<162; j++){
    quantumbase.ledState[0].u8ColorRatios[TRILED_R] = (!((j+3)%3))?255:0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_B] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_R] = (!((j+2)%3))?255:0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_B] = 0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_R] = (!((j+1)%3))?255:0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_B] = 0;
    quantumbase.u16Properties = (j%5 + 1)*9;
    QUANTUMFIFO_Push(quantumbase);
  }
  
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
  /*
  TRILED_SetLedState(TRILED_LEFT,state_1);
  TRILED_SetLedState(TRILED_CENTER,state_2);
  TRILED_SetLedState(TRILED_RIGHT,state_3);
  */
  TRILED_EnableModule();
  
  /* USER CODE END */
  
  while(1);
}