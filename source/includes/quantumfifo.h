#ifndef _QUANTUMFIFO_H_
#define _QUANTUMFIFO_H_

#include "quantum.h"

#define FIFO_SIZE       3

void QUANTUMFIFO_Initialize();
void QUANTUMFIFO_Push(QUANTUM quantum);
QUANTUM* QUANTUMFIFO_Pull();

#endif