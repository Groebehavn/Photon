#include "headers.h"

U32 u32FailureAddress = 0;

static FLASH_Status WriteDataSync(U32 u32Address, U8* u8Data, U32 u32Size)
{
  FLASH_Status eReturnValue = FLASH_COMPLETE;
  
  FLASH_Unlock();
  while(u32Size != 0)
  {
    eReturnValue = FLASH_ProgramByte(u32Address,*u8Data);
    if(FLASH_COMPLETE != eReturnValue)
    {
      u32FailureAddress = u32Address;
      break;
    }
    
    u32Size--;
    u32Address++;
    u8Data++;
  }
  FLASH_Lock();
  
  return eReturnValue;
}

FLASH_Status WriteProgramHeader(U32 u32Address, PROGRAM_HEADER progHeader)
{
  return WriteDataSync(u32Address, (U8*)&progHeader, sizeof(PROGRAM_HEADER));
}

FLASH_Status EraseProgram(int num)
{
  //TODO
  return FLASH_COMPLETE;
}

FLASH_Status WriteQuantum(U32 u32Address, QUANTUM quantum)
{
  return WriteDataSync(u32Address, (U8*)&quantum, sizeof(QUANTUM));
}

QUANTUM ReadQuantum(U32 u32Address)
{
  //TODO
  //return 0;
}

PROGRAM_HEADER ReadHeader(U32 u32Address)
{
  //TODO
  //return 0;
}