#include "headers.h"

static QSERVER_STATE ServerState = {
  BUFFERSTATE_INITVALUE,
  TICKCOUNTER_INITVALUE,
  TICKCOUNTER_INITVALUE,
  HMSCOUNTER_INITVALUE,
  CURRQUANTUM_INITVALUE,
};

static void QUANTUMSERVER_RefreshQuantumInServer()
{
  ServerState.CurrentQuantum = QUANTUMFIFO_Pull();
}

static void QUANTUMSERVER_SetLedStates()
{
  if(ServerState.CurrentQuantum == NULL)
  {
    //Not writing the TriLedProcess variable over
  }
  else{
    TRILED_SetLedState(TRILED_LEFT, ServerState.CurrentQuantum->ledState[TRILED_LEFT]);
    TRILED_SetLedState(TRILED_CENTER, ServerState.CurrentQuantum->ledState[TRILED_CENTER]);
    TRILED_SetLedState(TRILED_RIGHT, ServerState.CurrentQuantum->ledState[TRILED_RIGHT]);
  }
}

static inline U16 QUANTUMSERVER_GetTickCounter()
{
  return ServerState.TickCounter;
}

static inline U16 QUANTUMSERVER_GetHMilliSecondCounter()
{
  return ServerState.HMilliSecondCounter;
}

static inline void SynchronizeTick()
{
  ServerState.SynchronizedTickCounter = ServerState.TickCounter;
}

static void QUANTUMSERVER_SetTickCountersToDefault()
{
  ServerState.TickCounter = TICKCOUNTER_INITVALUE;
  SynchronizeTick();
  ServerState.HMilliSecondCounter = HMSCOUNTER_INITVALUE;
}

void QUANTUMSERVER_IncrementTickCounter()
{
  ServerState.TickCounter++;
  
  if(QUANTUMSERVER_GetTickCounter()%2 == 0 && QUANTUMSERVER_GetTickCounter() != 0)
  {
    ServerState.HMilliSecondCounter++;
  }
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

void QUANTUMSERVER_Tick()
{
  if(ServerState.TickCounter != ServerState.SynchronizedTickCounter)
  {
    SynchronizeTick();
    if(QUANTUMSERVER_GetHMilliSecondCounter()
       >
       (ServerState.CurrentQuantum->u16Properties & HOLDTIME_MASK))
    {
      //Because u16Properties&HOLDTIME_MASK == 0 means 0+1 * 100ms hold time
      QUANTUMSERVER_RefreshQuantumInServer();
      QUANTUMSERVER_SetLedStates();
      
      QUANTUMSERVER_SetTickCountersToDefault();
    }
  }
}

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
  QUANTUMSERVER_SetTickCountersToDefault();
  QUANTUMFIFO_Initialize();
}

QUANTUM* QUANTUMSERVER_GetCurrentQuantum()
{
  return ServerState.CurrentQuantum;
}