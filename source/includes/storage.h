#ifndef _STORAGE_H_
#define _STORAGE_H_

#define         STORAGE_START_ADDR      0x08010000
#define         STORAGE_END_ADDR        0x08100000
#define         STORAGE_ADDR_MASK       0x081F0000
#define         STORAGE_ADDR_INCREMENT  0x00010000        
#define         STORAGE_IN_ONE_CYCLE    2

typedef __packed struct t_sLOAD_STATUS
{
  U32 u32CurrentProgramAddress;
  U16 u16QuantumsToLoad;
}LOAD_STATUS;

#endif