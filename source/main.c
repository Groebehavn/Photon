#include "headers.h"

void main(){
  /*
  */
  
  //triled_test();
  //flashapi_test();
  storage_test();

  SystemInit();
  __enable_interrupt();
  
  GPIO_Initialize();
  TIMER_Initialize();
  TRILED_Initialize();
  QUANTUMSERVER_Initialize();
  STORAGE_Initialize();
  
  QUANTUMSERVER_EnableModule();
  TRILED_EnableModule();
  
  while(1){
    QUANTUMSERVER_Tick();
    TRILED_Tick();
  }
}