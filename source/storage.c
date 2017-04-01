#include "headers.h"

static LOAD_STATUS loadStatus;


static inline bool checkName(PROGRAM_HEADER* header)
{
  U8 u8Data[3] = {0x4C, 0x50, 0x50};    //LPP
  return (memcmp(header->u8Name,u8Data,3) == 0);
}

static bool checkGeneration(PROGRAM_HEADER* header)
{
  return (header->u8Generation == 1);
}

static bool checkTimeout(PROGRAM_HEADER* header)
{
  return (header->u16Timeout <= 3600);
}

static bool STORAGE_CheckHeader(void* address, PROGRAM_HEADER* header)
{
  memcpy(header,address,sizeof(PROGRAM_HEADER));
  
  return (checkName(header) && checkGeneration(header) && checkTimeout(header));
}

static U32 STORAGE_GetNextProgramAddress(U32 u32PrevAddress)
{
  U32 u32Address = u32PrevAddress & STORAGE_ADDR_MASK;
  u32Address = u32Address + STORAGE_ADDR_INCREMENT;
  
  if(u32Address >= STORAGE_END_ADDR)
  {
    u32Address = STORAGE_START_ADDR;
  }
  
  return u32Address;
}

static void STORAGE_SeachNextProgram()
{
  U32 i = 0;
  PROGRAM_HEADER header;
  U32 u32Address = loadStatus.u32CurrentProgramAddress;
  
  for(i=0; i<((STORAGE_END_ADDR-STORAGE_START_ADDR)/STORAGE_ADDR_INCREMENT); i++)
  {
    u32Address = STORAGE_GetNextProgramAddress(u32Address);
    if(STORAGE_CheckHeader((void*)u32Address, &header))
    {
      loadStatus.u16QuantumsToLoad = header.u16Length;
      loadStatus.u32CurrentProgramAddress = u32Address;
      break;
    }
  }
  
  if(i == ((STORAGE_END_ADDR-STORAGE_START_ADDR)/STORAGE_ADDR_INCREMENT))
  {
    loadStatus.u16QuantumsToLoad = 0;
    //TODO: ERROR STATE - végigiteráltunk minden programhelyen, és nincs program
    //és ez nincs igazán végiggondolva itt, elvileg a 0 majd reseteli a state
    //machine-t.
  }
  
}

void STORAGE_Initialize()
{
  //TODO:
  //FLASH_SetLatency(FLASH_Latency_5);
  //FLASH_Unlock();
  //FLASH_ClearFlag( FLASH_FLAG_EOP |  FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
  //FLASH_EraseSector(FLASH_Sector_5 , VoltageRange_3);
  //FLASH_ProgramWord(0x08020000l,0x5a5a5a5al);
  //FLASH_ProgramDoubleWord(0x08020010l ,0x5A5A5A5A5A5A5A5Al);
  //FLASH_Lock();
  //:TODO
  
  loadStatus.u32CurrentProgramAddress = STORAGE_END_ADDR;
  loadStatus.u16QuantumsToLoad = 0;
}

void STORAGE_InitializeNextProgram()
{
  if(loadStatus.u16QuantumsToLoad > 0)
  {
    //TODO: Ez így baj lenne, már van folyamatban betöltés, fail
  }
  else
  {
    STORAGE_SeachNextProgram();
    //loadStatus.u16QuantumsToLoad -= STORAGE_IN_ONE_CYCLE;
    //loadStatus.u32CurrentProgramAddress += STORAGE_IN_ONE_CYCLE*sizeof(QUANTUM);
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
      
      loadStatus.u32CurrentProgramAddress += loadStatus.u16QuantumsToLoad*sizeof(QUANTUM);
      loadStatus.u16QuantumsToLoad = 0;
    }
  }
}