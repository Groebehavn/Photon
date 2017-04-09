#include "headers.h"

static QSERVER_STATE ServerState = {
  BUFFERSTATE_INITVALUE,
  TICKCOUNTER_INITVALUE,
  TICKCOUNTER_INITVALUE,
  TICKCOUNTER_INITVALUE,
  TICKCOUNTER_INITVALUE,
  HMSCOUNTER_INITVALUE,
  CURRQUANTUM_INITVALUE,
};

static void RefreshQuantumInServer()
{
  ServerState.CurrentQuantum = QUANTUMFIFO_Pull();
}

static void SetLedStates()
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

static inline U16 GetTickCounter()
{
  return ServerState.TickCounter;
}

static inline U16 GetHMilliSecondCounter()
{
  return ServerState.HMilliSecondCounter;
}

static inline void SynchronizeTick()
{
  ServerState.SynchronizedTickCounter = ServerState.TickCounter;
}

static void SetTickCountersToDefault()
{
  ServerState.TickCounter = TICKCOUNTER_INITVALUE;
  ServerState.SynchronizedTickCounter = TICKCOUNTER_INITVALUE;
  ServerState.TickMargin = TICKCOUNTER_INITVALUE;
  ServerState.HMilliSecondCounter = HMSCOUNTER_INITVALUE;
}

static void SaveAndResetThreshold()
{
  if(ServerState.MaxMarginBetweenSync < ServerState.TickMargin)
  {
    ServerState.MaxMarginBetweenSync = ServerState.TickMargin;
  }
  ServerState.TickMargin = 0;
}

void QUANTUMSERVER_IncrementTickCounter()
{
  ServerState.TickCounter++;
  
  if(GetTickCounter()%2 == 0 && GetTickCounter() != 0)
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
    if(GetHMilliSecondCounter()
       >
       (ServerState.CurrentQuantum->u16Properties & HOLDTIME_MASK))
    {
      //Because u16Properties&HOLDTIME_MASK == 0 means 0+1 * 100ms hold time
      RefreshQuantumInServer();
      SetLedStates();
      STM_EVAL_LEDToggle(LED6);
      
      SetTickCountersToDefault();
    }
    SaveAndResetThreshold();
  }
  else
  {
    ServerState.TickMargin++;
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
  SetTickCountersToDefault();
  QUANTUMFIFO_Initialize();
}

QUANTUM* QUANTUMSERVER_GetCurrentQuantum()
{
  return ServerState.CurrentQuantum;
}