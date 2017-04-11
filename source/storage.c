#include "headers.h"

static LOAD_STATUS loadStatus;

static bool CheckName(PROGRAM_HEADER* header)
{
  U8 u8Data[3] = {0x4C, 0x50, 0x50};    //LPP
  return (memcmp(header->u8Name,u8Data,3) == 0);
}

static inline bool CheckGeneration(PROGRAM_HEADER* header)
{
  return (header->u8Generation == 1);
}

static inline bool CheckTimeout(PROGRAM_HEADER* header)
{
  return (header->u16Timeout <= 3600);
}

static bool CheckHeader(void* address, PROGRAM_HEADER* header)
{
  memcpy(header,address,sizeof(PROGRAM_HEADER));
  
  return (CheckName(header) && CheckGeneration(header) && CheckTimeout(header));
}

static U32 GetNextProgramAddress(U32 u32PrevAddress)
{
  U32 u32Address = u32PrevAddress & STORAGE_ADDR_MASK;
  u32Address = u32Address + STORAGE_ADDR_INCREMENT;
  
  if(u32Address >= STORAGE_END_ADDR)
  {
    u32Address = STORAGE_START_ADDR;
  }
  
  return u32Address;
}

static void SeachNextProgram()
{
  U32 i = 0;
  PROGRAM_HEADER header;
  U32 u32Address = loadStatus.u32CurrentProgramAddress;
  
  for(i=0; i<((STORAGE_END_ADDR-STORAGE_START_ADDR)/STORAGE_ADDR_INCREMENT); i++)
  {
    u32Address = GetNextProgramAddress(u32Address);
    if(CheckHeader((void*)u32Address, &header))
    {
      loadStatus.u16QuantumsToLoad = header.u16Length;
      loadStatus.u32CurrentProgramAddress = u32Address + sizeof(PROGRAM_HEADER);
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
  loadStatus.u32CurrentProgramAddress = STORAGE_END_ADDR;
  loadStatus.u16QuantumsToLoad = 0;
  
  SystemState.bStartLoad = true;
  
  STORAGE_InitializeNextProgram();
}

void STORAGE_InitializeNextProgram()
{
  if(loadStatus.u16QuantumsToLoad > 0)
  {
    //TODO: Ez így baj lenne, már van folyamatban betöltés, fail
  }
  else
  {
    if(SystemState.bStartLoad == true)
    {
      SeachNextProgram();
      
      loadStatus.bLoadInProgress = true;
      
      SystemState.bStartLoad = false;
      SystemState.bLoadFinished = false;
    }
  }
}

void STORAGE_LoadProgramCyclically()
{
  U8 u8i;
  QUANTUM quantum[STORAGE_IN_ONE_CYCLE];
  
  if(loadStatus.u16QuantumsToLoad == 0)
  {
    if(loadStatus.bLoadInProgress == true)
    {
      loadStatus.bLoadInProgress = false;
      
      SystemState.bLoadFinished = true;
    }
  }
  else{
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
      memcpy(quantum,(void*)loadStatus.u32CurrentProgramAddress,loadStatus.u16QuantumsToLoad*sizeof(QUANTUM));
      
      for(u8i = 0;u8i<loadStatus.u16QuantumsToLoad;u8i++){
        QUANTUMFIFO_Push(quantum[u8i]);
      }
      
      loadStatus.u32CurrentProgramAddress += loadStatus.u16QuantumsToLoad*sizeof(QUANTUM);
      loadStatus.u16QuantumsToLoad = 0;
    }
  }
}

void STORAGE_Tick()
{
  STORAGE_InitializeNextProgram();
  STORAGE_LoadProgramCyclically();
}
  