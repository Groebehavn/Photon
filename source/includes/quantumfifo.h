#ifndef _QUANTUMFIFO_H_
#define _QUANTUMFIFO_H_

#define FIFO_SIZE       4096

void QUANTUMFIFO_Initialize();
void QUANTUMFIFO_Push(QUANTUM quantum);
QUANTUM* QUANTUMFIFO_Pull();
void QUANTUMFIFO_EmptyFifo();
bool QUANTUMFIFO_IsOverrun();
bool QUANTUMFIFO_IsFull();

#endif