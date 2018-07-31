#include "headers.h"

static void vcp_test_init()
{
  SystemInit();
  __enable_interrupt();
  GPIO_Initialize();
  TIMER_Initialize();
  TRILED_Initialize();
  QUANTUMSERVER_Initialize();
  STORAGE_Initialize();
  
  TM_USB_VCP_Init();
}

void vcp_test(){
  U8 u8Timer = 100;
  QUANTUM quantumbase;
  PROGRAM_HEADER pheader;
  PROGRAM_HEADER pheader2;
  U8* u8P;
  U64* ppheader;
  U64* ppheader2;
  U32 u32Address;
  U32 u32Address2;
  U64 u64CopyTarget = 0;
  
  vcp_test_init();
  
  TRILED_EnableModule();
  QUANTUMSERVER_EnableModule();
  
  while(1){
    STORAGE_Tick();
    QUANTUMSERVER_Tick();
    TRILED_Tick();
    COMMUNICATION_Tick();
  }
}