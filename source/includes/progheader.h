#ifndef _PROGHEADER_H_
#define _PROGHEADER_H_

typedef __packed struct t_sPROGRAM_HEADER
{
  U16 u16Length;
  U16 u16Timeout;
  U8 u8Generation;
  U8 u8Name[3];
}PROGRAM_HEADER;

typedef union t_uPROGRAM_HEADER
{
  PROGRAM_HEADER header;
  U8 u8Data[8];
}uPROGRAM_HEADER;

#endif