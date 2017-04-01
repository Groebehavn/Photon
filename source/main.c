#include "headers.h"

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
  PROGRAM_HEADER pheader;
  U32* ppheader;
  U32* ppheader2;
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
  
  pheader.u16Length = 5;
  pheader.u16Timeout = 9;
  pheader.u8Generation = 1;
  pheader.u8Name[0] = 0x4C;
  pheader.u8Name[1] = 0x50; 
  pheader.u8Name[2] = 0x50;
  
  U32 asd = (U32)&pheader;
  ppheader = (U32*)asd;
  ppheader2 = (U32*)(asd+4);
  
  FLASH_Unlock();
  FLASH_ProgramWord(0x08080000l,(U32)(*ppheader));
  FLASH_ProgramWord(0x08080004l,(U32)(*ppheader2));
  FLASH_Lock();
  
  
  SystemInit();
  __enable_interrupt();

  /* USER CODE START */
  
  GPIO_Initialize();
  TIMER_Initialize();
  TRILED_Initialize();
  QUANTUMSERVER_Initialize();
  STORAGE_Initialize();
  
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
    //QUANTUMFIFO_Push(quantumbase);
    //TODO: Itt kéne beírni a flash-be a quantumot, hogy tesztelni lehessen a quantum másolást a while(1)-ben odalent!
  }
  
  QUANTUMSERVER_EnableModule();
  
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
  
  //TODO: Ez nem kell ám ide!!!!
  SYS_SetLoadInitialize();
  
  while(1){
    QUANTUMSERVER_Tick();
    TRILED_Tick();
    
    if(SYS_GetStartLoad())
    {
      STORAGE_LoadProgramCyclically();
    }
    
    if(SYS_GetLoadInitialize())
    {
      STORAGE_InitializeNextProgram();
    }
    
    if(SYS_GetRecievedData())
    {
      SYS_ResetRecievedData();
    }
  }
}