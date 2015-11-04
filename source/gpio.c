#include "systypes.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_gpio.h"
#include "gpio.h"

const uint16_t GPIO_LEDLEFT[3]   = {
  RGBLED_LEFT_R_GPIO_PIN,
  RGBLED_LEFT_G_GPIO_PIN,
  RGBLED_LEFT_B_GPIO_PIN
};
const uint16_t GPIO_LEDCENTER[3] = {
  RGBLED_CENTER_R_GPIO_PIN,
  RGBLED_CENTER_G_GPIO_PIN,
  RGBLED_CENTER_B_GPIO_PIN
};
const uint16_t GPIO_LEDRIGHT[3]  = {
  RGBLED_RIGHT_R_GPIO_PIN,
  RGBLED_RIGHT_G_GPIO_PIN,
  RGBLED_RIGHT_B_GPIO_PIN
};
const uint16_t* GPIO_LEDPINS[3]  = {
  GPIO_LEDLEFT,
  GPIO_LEDCENTER,
  GPIO_LEDRIGHT
};

/*
Initializes discovery and PCB GPIOs
*/
void GPIO_Initialize(void)
{
  GPIO_DiscoveryLedInit();
  GPIO_DiscoveryButtonInit();
  GPIO_TriLedInit();
  GPIO_UserButtonInit();
}

/*
Initializes the RGB leds on the PCB
*/
static void GPIO_TriLedInit(void)
{
  GPIO_InitTypeDef portinit;	                //GPIO Init struktúra
  
  RCC_AHB1PeriphClockCmd(RGBLED_PERIPH_CLOCK,ENABLE);

  portinit.GPIO_Mode=GPIO_Mode_OUT;
  portinit.GPIO_OType=GPIO_OType_PP;
  portinit.GPIO_Pin=
    GPIO_LEDLEFT[0]|GPIO_LEDLEFT[1]|GPIO_LEDLEFT[2]|
    GPIO_LEDCENTER[0]|GPIO_LEDCENTER[1]|GPIO_LEDCENTER[2]|
    GPIO_LEDRIGHT[0]|GPIO_LEDRIGHT[1]|GPIO_LEDRIGHT[2];
  portinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
  portinit.GPIO_Speed=GPIO_Speed_2MHz;
  GPIO_Init(RGBLED_GPIO_PORT,&portinit);
}

/*
Initializes the user button on the PCB
*/
static void GPIO_UserButtonInit(void)
{
  GPIO_InitTypeDef portinit;	                //GPIO Init struktúra
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
  
  portinit.GPIO_Mode=GPIO_Mode_IN;
  portinit.GPIO_OType=GPIO_OType_PP;
  portinit.GPIO_Pin=GPIO_Pin_5;
  portinit.GPIO_PuPd=GPIO_PuPd_NOPULL;
  portinit.GPIO_Speed=GPIO_Speed_2MHz;
  GPIO_Init(GPIOE,&portinit); //Gomb  
}

/*
Initializes the discovery board's leds
*/
static void GPIO_DiscoveryLedInit(void)
{
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
}

/*
Sets the discovery board's button to EXTI0 source
*/
static void GPIO_DiscoveryButtonInit(void)
{
  STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_EXTI);
}