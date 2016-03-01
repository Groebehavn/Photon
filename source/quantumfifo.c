#include "quantumfifo.h"
#include <stdio.h>
#include <string.h>

static QUANTUM fifo[FIFO_SIZE];
static U16 pushPosition;
static U16 pullPosition;
static bool fifoFull;
static bool fifoOverrun;
static inline U16 QUANTUMFIFO_IncrementPosition(U16* pos){
  if(*pos < (FIFO_SIZE-1)){
    return (*pos + 1);
  }
  else{
    return 0;
  }
}

void QUANTUMFIFO_Initialize()
{
  U16 i;
  for(i=0; i<FIFO_SIZE; i++){
    memset(&fifo[i], 0, sizeof(QUANTUM));
  }
  
  pushPosition = 0;
  pullPosition = 0;
  fifoFull = false;
  fifoOverrun = false;
}

void QUANTUMFIFO_Push(QUANTUM quantum)
{
  if(fifoFull == true)
  {
    fifoOverrun = true;
  }
  fifo[pushPosition] = quantum;
  pushPosition = QUANTUMFIFO_IncrementPosition(&pushPosition);
  if(pushPosition == pullPosition)
  {
    fifoFull = true;
  }
}

QUANTUM* QUANTUMFIFO_Pull()
{
  U16 position;
  
  if(pushPosition == pullPosition && fifoFull == false)
  {
    return NULL;
  }
  else{
    position = pullPosition;
    pullPosition = QUANTUMFIFO_IncrementPosition(&pullPosition);
    fifoFull = false;
    return &fifo[position];
  }
}

void QUANTUMFIFO_EmptyFifo()
{
  pullPosition = pushPosition;
  fifoFull = false;
  fifoOverrun = false;
}

bool QUANTUMFIFO_IsOverrun()
{
  return fifoOverrun;
}

