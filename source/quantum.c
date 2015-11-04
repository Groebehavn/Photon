#include "quantum.h"

bool isInterpolated(QUANTUM* lightQuantum)
{
  return ((*lightQuantum).u16Properties & 0x8000) != 0;
}

U16 getHoldTime(QUANTUM* lightQuantum)
{
  return ((*lightQuantum).u16Properties & 0x7FFF);
}