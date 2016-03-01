#include <string.h>
#include "stm32f4_discovery.h"
#include "quantum.h"
#include "quantumfifo.h"
#include "quantumserver.h"

extern volatile TRILED_PROCDESC gTriLedProcess;

static QSERVER_STATE ServerState = {
  BUFFERSTATE_INITVALUE,
  TICKCOUNTER_INITVALUE,
  HMSCOUNTER_INITVALUE,
  CURRQUANTUM_INITVALUE,
};

void QUANTUMSERVER_DisableModule()
{
  TIM_Cmd(TIM5,DISABLE);
}

void QUANTUMSERVER_EnableModule()
{
  TIM_Cmd(TIM5,ENABLE);
}

void QUANTUMSERVER_Initialize()
{
  QUANTUMSERVER_DisableModule();
  QUANTUMFIFO_Initialize();
}


QUANTUM QUANTUMSERVER_GetCurrentQuantum()
{
  return *ServerState.CurrentQuantum;
}

void QUANTUMSERVER_RefreshQuantumInServer()
{
  ServerState.CurrentQuantum = QUANTUMFIFO_Pull();
}

void QUANTUMSERVER_SetLedStates()
{
  if(ServerState.CurrentQuantum == NULL)
  {
    //Not writing the TriLedProcess variable over
  }
  else{
    gTriLedProcess.aLedStates[0] = ServerState.CurrentQuantum->ledState[0];
    gTriLedProcess.aLedStates[1] = ServerState.CurrentQuantum->ledState[1];
    gTriLedProcess.aLedStates[2] = ServerState.CurrentQuantum->ledState[2];
  }
}

U16 QUANTUMSERVER_GetTickCounter()
{
  return ServerState.TickCounter;
}

void QUANTUMSERVER_IncrementTickCounter()
{
  ServerState.TickCounter++;
}

void QUANTUMSERVER_SetTickCounterToDefault()
{
  ServerState.TickCounter = TICKCOUNTER_INITVALUE;
}

void QUANTUMSERVER_IncrementHMilliSecondCounter()
{
  ServerState.HMilliSecondCounter++;
}

U16 QUANTUMSERVER_GetHMilliSecondCounter()
{
  return ServerState.HMilliSecondCounter;
}

void QUANTUMSERVER_SetHMilliSecondCounterToDefault()
{
  ServerState.HMilliSecondCounter = HMSCOUNTER_INITVALUE;
}

void QUANTUMSERVER_PushProgramToFifo(U8 u8Position)
{
  QUANTUM quantum;
  U16 i=0;
  
  for(i=0; i<FIFO_SIZE; i++){
    memcpy((QUANTUM*)&quantum,(QUANTUM*)PROGRAM1_BASE + (sizeof(QUANTUM) * i),sizeof(QUANTUM));
    QUANTUMFIFO_Push(quantum);
  }
}

