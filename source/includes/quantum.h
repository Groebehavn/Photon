#ifndef _QUANTUM_H_
#define _QUANTUM_H_

#include "systypes.h"
#include "triled.h"

typedef __packed struct t_sQUANTUM
{
  TRILED_STATE ledState[3];
  U16 u16Properties;
}QUANTUM;

typedef union t_uQUANTUM
{
  QUANTUM quantum;
  U8 u8Data[11];
}uQUANTUM;

#endif