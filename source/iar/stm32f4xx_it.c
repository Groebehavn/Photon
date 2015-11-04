/**
  ******************************************************************************
  * @file    TIM_PWM_Input/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "systypes.h"
#include "triled.h"
#include "trileddriver.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern volatile TRILED_PROCDESC gTriLedProcess;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  * @author PT
  */
void TIM3_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  * @author PT
  */
void TIM5_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM5,TIM_IT_Update)==true)
  {
    TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
  }
}

/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  * @author PT
  */
void TIM4_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM4,TIM_IT_Update)==true)
  {
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    
    if(gTriLedProcess.u8Progress == 255)
    {
      gTriLedProcess.u8Progress = 0;
    }
    
    if(gTriLedProcess.bEnabled == true)
    {
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_LEFT,TRILED_R);
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_LEFT,TRILED_G);
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_LEFT,TRILED_B);
      
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_CENTER,TRILED_R);
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_CENTER,TRILED_G);
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_CENTER,TRILED_B);
      
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_RIGHT,TRILED_R);
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_RIGHT,TRILED_G);
      TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_RIGHT,TRILED_B);
    }
    
     gTriLedProcess.u8Progress++;
  }
}

/**
  * @brief  This function handles ADC global interrupt request.
  * @param  None
  * @retval None
  * @author PT
  */
void ADC_IRQHandler(void)
{
}

void DMA2_Stream0_IRQHandler(void)
{
}

/**
  * @brief  This function handles EXT0 global interrupt request.
  * @param  None
  * @retval None
  * @author PT
  */
void EXTI0_IRQHandler(void)
{
  
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
