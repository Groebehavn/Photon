#include "quantumfifo.h"
#include <stdio.h>
#include <string.h>

static QUANTUM fifo[FIFO_SIZE];
static U8 pushPosition;
static U8 pullPosition;

void QUANTUMFIFO_Initialize()
{
  U8 i;
  for(i=0; i<FIFO_SIZE; i++){
    memset(&fifo[i], 0, sizeof(QUANTUM));
  }
  
  pushPosition = 0;
  pullPosition = 0;
}

static inline U8 QUANTUMFIFO_IncrementPosition(U8* pos){
  if(*pos < (FIFO_SIZE-1)){
    return (*pos + 1);
  }
  else{
    return 0;
  }
}

void QUANTUMFIFO_Push(QUANTUM quantum)
{
  fifo[pushPosition] = quantum;
  pushPosition = QUANTUMFIFO_IncrementPosition(&pushPosition);
}

QUANTUM* QUANTUMFIFO_Pull()
{
  int position;
  
  if(pushPosition == pullPosition)
  {
    return NULL;
  }
  else{
    position = pullPosition;
    pullPosition = QUANTUMFIFO_IncrementPosition(&pullPosition);
    return &fifo[position];
  }
}

