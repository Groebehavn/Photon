#include "headers.h"

void flashapi_test()
{
  QUANTUM quantumbase;
  PROGRAM_HEADER header;
  
  FLASH_Unlock();
  FLASH_EraseSector(FLASH_Sector_5 , VoltageRange_3);
  FLASH_EraseSector(FLASH_Sector_6 , VoltageRange_3);
  FLASH_EraseSector(FLASH_Sector_7 , VoltageRange_3);
  FLASH_EraseSector(FLASH_Sector_8 , VoltageRange_3);
  FLASH_EraseSector(FLASH_Sector_9 , VoltageRange_3);
  FLASH_Lock();
  
  //First program
  header.u16Length = 9;
  header.u16Timeout = 1;
  header.u8Generation = 1;
  header.u8Name[0] = 0x4C;
  header.u8Name[1] = 0x50; 
  header.u8Name[2] = 0x50;
  
  WriteProgramHeader(0x08060000,header);
  
  for(int j=0; j<9; j++){
    quantumbase.ledState[0].u8ColorRatios[TRILED_R] = (!((j+3)%3))?255:0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_G] = 88;
    quantumbase.ledState[0].u8ColorRatios[TRILED_B] = 44;
    quantumbase.ledState[1].u8ColorRatios[TRILED_R] = (!((j+2)%3))?255:0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_G] = 88;
    quantumbase.ledState[1].u8ColorRatios[TRILED_B] = 44;
    quantumbase.ledState[2].u8ColorRatios[TRILED_R] = (!((j+1)%3))?255:0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_G] = 88;
    quantumbase.ledState[2].u8ColorRatios[TRILED_B] = 44;
    //quantumbase.u16Properties = (j%5 + 1)*9;
    //1 quantum / 1 sec change verified
    quantumbase.u16Properties = 9;
    
    WriteQuantum(0x08060008 + j*sizeof(QUANTUM),quantumbase);
  }
  
  //Second program
  header.u16Length = 9;
  header.u16Timeout = 2;
  header.u8Generation = 1;
  header.u8Name[0] = 0x4C;
  header.u8Name[1] = 0x50; 
  header.u8Name[2] = 0x50;
  
  WriteProgramHeader(0x08040000,header);
  
  for(int j=0; j<9; j++){
    quantumbase.ledState[0].u8ColorRatios[TRILED_R] = 0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_G] = (!((j+3)%3))?255:0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_B] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_R] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_B] = (!((j+2)%3))?255:0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_R] = (!((j+1)%3))?255:0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_B] = 0;
    //quantumbase.u16Properties = (j%5 + 1)*9;
    //1 quantum / 1 sec change verified
    quantumbase.u16Properties = 15;
    
    WriteQuantum(0x08040008 + j*sizeof(QUANTUM),quantumbase);
  }
  
  //Third program
  header.u16Length = 99;
  header.u16Timeout = 2;
  header.u8Generation = 1;
  header.u8Name[0] = 0x4C;
  header.u8Name[1] = 0x50; 
  header.u8Name[2] = 0x50;
  
  WriteProgramHeader(0x08080000,header);
  
  for(int j=0; j<99; j++){
    quantumbase.ledState[0].u8ColorRatios[TRILED_R] = 0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_G] = (!((j+3)%3))?255:0;
    quantumbase.ledState[0].u8ColorRatios[TRILED_B] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_R] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[1].u8ColorRatios[TRILED_B] = (!((j+2)%3))?255:0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_R] = (!((j+1)%3))?255:0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_G] = 0;
    quantumbase.ledState[2].u8ColorRatios[TRILED_B] = 0;
    //quantumbase.u16Properties = (j%5 + 1)*9;
    //1 quantum / 1 sec change verified
    quantumbase.u16Properties = 0;
    
    WriteQuantum(0x08080008 + j*sizeof(QUANTUM),quantumbase);
  }
}