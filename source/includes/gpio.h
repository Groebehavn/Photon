#ifndef _GPIO_H_
#define _GPIO_H_

/*Defines*/
#define RGBLED_GPIO_PORT                GPIOE
#define RGBLED_PERIPH_CLOCK             RCC_AHB1Periph_GPIOE        
  
#define RGBLED_LEFT_R_GPIO_PIN          GPIO_Pin_8
#define RGBLED_CENTER_R_GPIO_PIN        GPIO_Pin_11
#define RGBLED_RIGHT_R_GPIO_PIN         GPIO_Pin_14

#define RGBLED_LEFT_G_GPIO_PIN          GPIO_Pin_9
#define RGBLED_CENTER_G_GPIO_PIN        GPIO_Pin_12
#define RGBLED_RIGHT_G_GPIO_PIN         GPIO_Pin_15

#define RGBLED_LEFT_B_GPIO_PIN          GPIO_Pin_7
#define RGBLED_CENTER_B_GPIO_PIN        GPIO_Pin_10
#define RGBLED_RIGHT_B_GPIO_PIN         GPIO_Pin_13

#define RGBLED_GPIO_LEFTPINS            RGBLED_LEFT_R_GPIO_PIN|RGBLED_LEFT_G_GPIO_PIN|RGBLED_LEFT_B_GPIO_PIN
#define RGBLED_GPIO_CENTERPINS          RGBLED_CENTER_R_GPIO_PIN|RGBLED_CENTER_G_GPIO_PIN|RGBLED_CENTER_B_GPIO_PIN
#define RGBLED_GPIO_RIGHTPINS           RGBLED_RIGHT_R_GPIO_PIN|RGBLED_RIGHT_G_GPIO_PIN|RGBLED_RIGHT_B_GPIO_PIN
#define RGBLED_GPIO_ALLPINS             RGBLED_GPIO_LEFTPINS|RGBLED_GPIO_CENTERPINS|RGBLED_GPIO_RIGHTPINS

/*Prototypes*/
void GPIO_Initialize(void);
static void GPIO_TriLedInit(void);
static void GPIO_UserButtonInit(void);
static void GPIO_DiscoveryLedInit(void);
static void GPIO_DiscoveryButtonInit(void);

#endif