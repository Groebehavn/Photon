#include "systypes.h"
#include "quantum.h"
#include "quantumfifo.h"
#include "statemachine.h"
#include "progheader.h"
#include "storage.h"

static LOAD_STATUS loadStatus;

static bool STORAGE_CheckHeader(void* address, PROGRAM_HEADER* header)
{
  memcpy(header,address,sizeof(PROGRAM_HEADER));
  
  //TODO
  return true;
}

static U32 STORAGE_GetNextProgramAddress()
{
  U32 u32Address = loadStatus.u32CurrentProgramAddress & STORAGE_ADDR_MASK;
  u32Address = u32Address + STORAGE_ADDR_INCREMENT;
  
  if(u32Address >= STORAGE_END_ADDR)
  {
    u32Address = STORAGE_START_ADDR;
  }
  
  return u32Address;
}

static void STORAGE_SeachNextProgram()
{
  PROGRAM_HEADER header;
  U32 u32Address = STORAGE_GetNextProgramAddress();
  
  STORAGE_CheckHeader((void*)u32Address, &header);
}

void STORAGE_Initialize()
{
  loadStatus.u32CurrentProgramAddress = STORAGE_END_ADDR;
  loadStatus.u16QuantumsToLoad = 0;
}

void STORAGE_InitializeNextProgram()
{
  if(loadStatus.u16QuantumsToLoad > 0)
  {
    
  }
  else
  {
    
  }
  
  SYS_SetStartLoad();
  SYS_ResetLoadInitialize();
}

void STORAGE_LoadProgramCyclically()
{
  U8 u8i;
  QUANTUM quantum[STORAGE_IN_ONE_CYCLE];
  
  if(loadStatus.u16QuantumsToLoad > (STORAGE_IN_ONE_CYCLE-1))
  {
    memcpy(quantum,(void*)loadStatus.u32CurrentProgramAddress,STORAGE_IN_ONE_CYCLE*sizeof(QUANTUM));
  
    for(u8i = 0;u8i<STORAGE_IN_ONE_CYCLE;u8i++){
      QUANTUMFIFO_Push(quantum[u8i]);
    }
    
    loadStatus.u16QuantumsToLoad -= STORAGE_IN_ONE_CYCLE;
    loadStatus.u32CurrentProgramAddress += STORAGE_IN_ONE_CYCLE*sizeof(QUANTUM);
  }
  else{
    if(loadStatus.u16QuantumsToLoad == 0)
    {
      SYS_ResetStartLoad();
    }
    else{
      memcpy(quantum,(void*)loadStatus.u32CurrentProgramAddress,loadStatus.u16QuantumsToLoad*sizeof(QUANTUM));
      
      for(u8i = 0;u8i<loadStatus.u16QuantumsToLoad;u8i++){
        QUANTUMFIFO_Push(quantum[u8i]);
      }
      
      loadStatus.u16QuantumsToLoad = 0;
      loadStatus.u32CurrentProgramAddress += loadStatus.u16QuantumsToLoad*sizeof(QUANTUM);
    }
  }
  
  
}