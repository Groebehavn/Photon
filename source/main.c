#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void main(){
  SystemInit();
  __enable_interrupt();

  /* USER CODE START */
  
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);
  STM_EVAL_LEDOn(LED5);
  STM_EVAL_LEDOn(LED6);
  
  /* USER CODE END */
}