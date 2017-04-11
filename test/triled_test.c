#include "headers.h"

//VERIFIED: 2017.04.09

extern TRILED_PROCDESC gTriLedProcess;

static void triled_test_init()
{
  SystemInit();
  __enable_interrupt();
  GPIO_Initialize();
  TIMER_Initialize();
  TRILED_Initialize();
  QUANTUMSERVER_Initialize();
}

void triled_test(){
  QUANTUM quantumbase;
  
  /*
  triled_test_init();
  */
  
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
  
  for(int j=0; j<15; j++){
    quantumbase.ledState[0].u8ColorRatios[TRILED_R] = (!((j+3)%3))?255:0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_B] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_R] = (!((j+2)%3))?255:0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_B] = 0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_R] = (!((j+1)%3))?255:0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_B] = 0;
    //quantumbase.u16Properties = (j%5 + 1)*9;
    //1 quantum / 1 sec change verified
    quantumbase.u16Properties = 9;
    
    QUANTUMFIFO_Push(quantumbase);
    //TODO: Itt kéne beírni a flash-be a quantumot, hogy tesztelni lehessen a quantum másolást a while(1)-ben odalent!
  }

  TRILED_EnableModule();
  QUANTUMSERVER_EnableModule();
  
  while(1){
    QUANTUMSERVER_Tick();
    TRILED_Tick();
  }
}