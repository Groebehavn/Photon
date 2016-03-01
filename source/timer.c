#include "systypes.h"
#include "timer.h"
#include "misc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

/*
Be aware that all the timer peripherals receive only SYSCLK/2!
*/
void TIMER_Initialize(){
  TIMER_TIM4_Init();                                                            //Light-quantum creation timer init
  TIMER_TIM5_Init();                                                            //Light-quantum change timer init
}

/*
Initializes TIM4 as the light-quantum creation 25kHz timer
The timer is disabled by default, can be enabled by triled.
*/
static void TIMER_TIM4_Init(){
  TIM_TimeBaseInitTypeDef initStructure;
  NVIC_InitTypeDef nvicStructure;
  
  //Enable clock on peripheral
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
  
  //Timer base init
  initStructure.TIM_Prescaler           = 42-1;                                 //84MHz to 2MHz
  initStructure.TIM_ClockDivision       = 0;                                    //0
  initStructure.TIM_CounterMode         = TIM_CounterMode_Up;                   //Counting up
  initStructure.TIM_Period              = 40-1;                                 //Downscaling to 25kHz
  initStructure.TIM_RepetitionCounter   = 0;                                    //Valid for only TIM1 and TIM8
  TIM_TimeBaseInit(TIM4,&initStructure);
    
  //**************************************************************************//
  //DISABLE TIMER
  
  TIM_Cmd(TIM4,DISABLE);
  TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
  TIM_SetCounter(TIM4,0);
  
  //**************************************************************************//
  //Configure NVIC
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               
  nvicStructure.NVIC_IRQChannel=TIM4_IRQn;                         
  nvicStructure.NVIC_IRQChannelPreemptionPriority=0;               
  nvicStructure.NVIC_IRQChannelSubPriority=0;                      
  nvicStructure.NVIC_IRQChannelCmd=ENABLE;                         

  NVIC_Init(&nvicStructure);
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
  
  //**************************************************************************//
}

/*
Initializes TIM5 as the light-quantum change 20Hz timer
The timer is disabled by default.  Up to 2x iterations/100ms,
to be able to switch colors smoothly.
*/
static void TIMER_TIM5_Init(){
  TIM_TimeBaseInitTypeDef initStructure;
  NVIC_InitTypeDef nvicStructure;
  
  //Enable clock on peripheral
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
  
  //Timer base init
  initStructure.TIM_Prescaler           = 21000-1;                              //84MHz to 4kHz
  initStructure.TIM_ClockDivision       = 0;                                    //0
  initStructure.TIM_CounterMode         = TIM_CounterMode_Up;                   //Counting up
  initStructure.TIM_Period              = (4*50)-1;                             //Downscaling to 20Hz
  initStructure.TIM_RepetitionCounter   = 0;                                    //Valid for only TIM1 and TIM8
  TIM_TimeBaseInit(TIM5,&initStructure);
    
  //**************************************************************************//
  //DISABLE TIMER
  
  TIM_Cmd(TIM5,DISABLE);
  TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
  TIM_SetCounter(TIM5,0);
  
  //**************************************************************************//
  //Configure NVIC
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  nvicStructure.NVIC_IRQChannel=TIM5_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority=1;
  nvicStructure.NVIC_IRQChannelSubPriority=1;
  nvicStructure.NVIC_IRQChannelCmd=ENABLE;

  NVIC_Init(&nvicStructure);
  TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
  
  //**************************************************************************//
}