#include "headers.h"

void storage_test(){
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
  
  pheader2.u16Length = 3;
  pheader2.u16Timeout = 2;
  pheader2.u8Generation = 1;
  pheader2.u8Name[0] = 0x4C;
  pheader2.u8Name[1] = 0x50; 
  pheader2.u8Name[2] = 0x50;
  
  u32Address = (U32)&pheader;
  u32Address2 = (U32)&pheader2;
  ppheader = (U64*) ((U32)&pheader) ;
  ppheader2 = (U64*) ((U32)&pheader2);
  
  //FLASH_Unlock();
  //FLASH_EraseSector(FLASH_Sector_5 , VoltageRange_3);
  //FLASH_EraseSector(FLASH_Sector_6 , VoltageRange_3);
  //FLASH_Lock();
  
  while(u8Timer-- != 0);
  
  u8P = (U8*)ppheader;
  
  FLASH_Unlock();
  FLASH_ProgramByte(0x08040000,*u8P);
  FLASH_ProgramByte(0x08040001,*(u8P+1));
  FLASH_ProgramByte(0x08040002,*(u8P+2));
  FLASH_ProgramByte(0x08040003,*(u8P+3));
  FLASH_ProgramByte(0x08040004,*(u8P+4));
  FLASH_ProgramByte(0x08040005,*(u8P+5));
  FLASH_ProgramByte(0x08040006,*(u8P+6));
  FLASH_ProgramByte(0x08040007,*(u8P+7));
  //FLASH_ProgramDoubleWord(0x08020010,*ppheader);
  //FLASH_ProgramDoubleWord(0x08040000,*ppheader2);
  FLASH_Lock();
  
  STORAGE_Initialize();
  
  STORAGE_LoadProgramCyclically();
}