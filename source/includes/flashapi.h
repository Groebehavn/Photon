#ifndef _FLASHAPI_H_
#define _FLASHAPI_H_

FLASH_Status WriteProgramHeader(U32 u32Address, PROGRAM_HEADER progHeader);

FLASH_Status EraseProgram(int num);

FLASH_Status WriteQuantum(U32 u32Address, QUANTUM quantum);

QUANTUM ReadQuantum(U32 u32Address);

PROGRAM_HEADER ReadHeader(U32 u32Address);

#endif