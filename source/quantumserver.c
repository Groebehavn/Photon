#include "headers.h"

static QSERVER_STATE ServerState = {
  TICKCOUNTER_INITVALUE,
  TICKCOUNTER_INITVALUE,
  HMSCOUNTER_INITVALUE,
  STATISTICS_INITVALUE,
  CURRQUANTUM_INITVALUE,
  NEXTQUANTUM_INITVALUE,
  INTERPOLATORACTIVE_INITVALUE
};

static inline U16 GetTickCounter()
{
  return ServerState.TickCounter;
}

static inline U16 GetHMilliSecondCounter()
{
  return ServerState.HMilliSecondCounter;
}

static inline U16 GetLengthOfCurrQuantumInHMS()
{
  // 0x0000 represents 100ms
  return (ServerState.CurrentQuantum->u16Properties & HOLDTIME_MASK) + 1;
}

static void SetQuantumDiffAndIncrement(U8* u8CurrColor, U8* u8NextColor, U8* u8Diff, bool* bIncrement)
{
  if(*u8CurrColor < *u8NextColor)
  {
    *u8Diff = *u8NextColor - *u8CurrColor;
    *bIncrement = true;
  }
  else
  {
    *u8Diff = *u8CurrColor - *u8NextColor;
    *bIncrement = false;
  }
}

static void ActualizeInterpolationData()
{
  U8 i;
  //TODO: *2 (Ticks / HMS)
  U16 u16Duration = GetLengthOfCurrQuantumInHMS() * 2;
  U8 ao8uDiffRed[3];
  U8 ao8uDiffGreen[3];
  U8 ao8uDiffBlue[3];
  
  if(ServerState.NextQuantum == NULL || ServerState.CurrentQuantum == NULL)
  {
    ServerState.InterpolationData.InterpolatorActiveInQuantum = false;
    return;
  }
  
  ServerState.InterpolationData.InterpolatorActiveInQuantum = (ServerState.CurrentQuantum->u16Properties & INTERPOLATION_MASK == INTERPOLATION_MASK);
  
  if(!ServerState.InterpolationData.InterpolatorActiveInQuantum)
  {
    return;
  }
  
  //Using a dummy quantum, filling with the current, and in the cycle, being
  //able to rewrite quantum values (in QUANTUM* it wouldn't be good...)
  ServerState.InterpolationData.InterpolatorDummyQuantum = *ServerState.CurrentQuantum;
  
  for(i=0; i<3; i++)
  {
    SetQuantumDiffAndIncrement(
      ServerState.CurrentQuantum->ledState[i].u8ColorRatios + TRILED_R,
      ServerState.NextQuantum->ledState[i].u8ColorRatios + TRILED_R,
      ao8uDiffRed+i,
      ServerState.InterpolationData.IncrementRed+i
        );
    
    SetQuantumDiffAndIncrement(
      ServerState.CurrentQuantum->ledState[i].u8ColorRatios + TRILED_G,
      ServerState.NextQuantum->ledState[i].u8ColorRatios + TRILED_G,
      ao8uDiffGreen+i,
      ServerState.InterpolationData.IncrementGreen+i
        );
    
    SetQuantumDiffAndIncrement(
      ServerState.CurrentQuantum->ledState[i].u8ColorRatios + TRILED_B,
      ServerState.NextQuantum->ledState[i].u8ColorRatios + TRILED_B,
      ao8uDiffBlue+i,
      ServerState.InterpolationData.IncrementBlue+i
        );
  }
  
  //Feed the deltas for periodical counting
  //(these will be added/subtracted in each cycle to the cummulative value)
  for(i=0; i<3; i++)
  {
    ServerState.InterpolationData.DeltaR[i] = (double)ao8uDiffRed[i] / (double)u16Duration;
    ServerState.InterpolationData.DeltaG[i] = (double)ao8uDiffGreen[i] / (double)u16Duration;
    ServerState.InterpolationData.DeltaB[i] = (double)ao8uDiffBlue[i] / (double)u16Duration;
  }
  
  //Reset cummulative counters representing the total counting value
  for(i=0; i<3; i++)
  {
    ServerState.InterpolationData.CummulativeR[i] = 0.0;
    ServerState.InterpolationData.CummulativeG[i] = 0.0;
    ServerState.InterpolationData.CummulativeB[i] = 0.0;
  }

}

static void Interpolate()
{
  if(ServerState.InterpolationData.InterpolatorActiveInQuantum == false)
  {
    return;
  }
  
  for(int i=0; i<3; i++)
  {
    ServerState.InterpolationData.CummulativeR[i] += ServerState.InterpolationData.DeltaR[i];
    ServerState.InterpolationData.CummulativeG[i] += ServerState.InterpolationData.DeltaG[i];
    ServerState.InterpolationData.CummulativeB[i] += ServerState.InterpolationData.DeltaB[i];
    
    if(ServerState.InterpolationData.IncrementRed[i] == false)
    {
      //Clipping at colorratio thus preventing overrun
      if(ServerState.InterpolationData.CummulativeR[i] > ServerState.CurrentQuantum->ledState[i].u8ColorRatios[0])
      {
        ServerState.InterpolationData.CummulativeR[i] = ServerState.CurrentQuantum->ledState[i].u8ColorRatios[0];
      }
    }
    else
    {
      //Clipping at 255-colorratio thus preventing overrun
      if(ServerState.InterpolationData.CummulativeR[i] > 0xFF-ServerState.CurrentQuantum->ledState[i].u8ColorRatios[0])
      {
        ServerState.InterpolationData.CummulativeR[i] = 0xFF-ServerState.CurrentQuantum->ledState[i].u8ColorRatios[0];
      }
    }
    
    if(ServerState.InterpolationData.IncrementGreen[i] == false)
    {
      //Clipping at colorratio thus preventing overrun
      if(ServerState.InterpolationData.CummulativeG[i] > ServerState.CurrentQuantum->ledState[i].u8ColorRatios[1])
      {
        ServerState.InterpolationData.CummulativeG[i] = ServerState.CurrentQuantum->ledState[i].u8ColorRatios[1];
      }
    }
    else
    {
      //Clipping at colorratio thus preventing overrun
      if(ServerState.InterpolationData.CummulativeG[i] > 0xFF-ServerState.CurrentQuantum->ledState[i].u8ColorRatios[1])
      {
        ServerState.InterpolationData.CummulativeG[i] = 0xFF-ServerState.CurrentQuantum->ledState[i].u8ColorRatios[1];
      }
    }
    
    if(ServerState.InterpolationData.IncrementBlue[i] == false)
    {
      //Clipping at colorratio thus preventing overrun
      if(ServerState.InterpolationData.CummulativeB[i] > ServerState.CurrentQuantum->ledState[i].u8ColorRatios[2])
      {
        ServerState.InterpolationData.CummulativeB[i] = ServerState.CurrentQuantum->ledState[i].u8ColorRatios[2];
      }
    }
    else
    {
      //Clipping at colorratio thus preventing overrun
      if(ServerState.InterpolationData.CummulativeB[i] > 0xFF-ServerState.CurrentQuantum->ledState[i].u8ColorRatios[2])
      {
        ServerState.InterpolationData.CummulativeB[i] = 0xFF-ServerState.CurrentQuantum->ledState[i].u8ColorRatios[2];
      }
    }
    
    if(ServerState.InterpolationData.IncrementRed[i] == true)
    {
      ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[i].u8ColorRatios[0] = 
        ServerState.CurrentQuantum->ledState[i].u8ColorRatios[0]
          + (U8)(ServerState.InterpolationData.CummulativeR[i]);
    }
    else
    {
      ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[i].u8ColorRatios[0] = 
        ServerState.CurrentQuantum->ledState[i].u8ColorRatios[0]
          - (U8)(ServerState.InterpolationData.CummulativeR[i]);
    }
    if(ServerState.InterpolationData.IncrementGreen[i] == true)
    {
      ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[i].u8ColorRatios[1] = 
        ServerState.CurrentQuantum->ledState[i].u8ColorRatios[1]
          + (U8)(ServerState.InterpolationData.CummulativeG[i]);
    }
    else
    {
      ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[i].u8ColorRatios[1] = 
        ServerState.CurrentQuantum->ledState[i].u8ColorRatios[1]
          - (U8)(ServerState.InterpolationData.CummulativeG[i]);
    }
    if(ServerState.InterpolationData.IncrementBlue[i] == true)
    {
      ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[i].u8ColorRatios[2] = 
        ServerState.CurrentQuantum->ledState[i].u8ColorRatios[2]
          + (U8)(ServerState.InterpolationData.CummulativeB[i]);
    }
    else
    {
      ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[i].u8ColorRatios[2] = 
        ServerState.CurrentQuantum->ledState[i].u8ColorRatios[2]
          - (U8)(ServerState.InterpolationData.CummulativeB[i]);
    }
  }
}

void QUANTUMSERVER_IncrementTickCounter()
{
  ServerState.TickCounter++;
  
  if(GetTickCounter()%2 == 0 && GetTickCounter() != 0)
  {
    ServerState.HMilliSecondCounter++;
  }
}

static void SignalStartLoad()
{
  if( QUANTUMFIFO_GetRemainingQuantumCount() <= 2 )
  {
    SystemState.bStartLoad = true;
  }
}

static void RefreshQuantumInServer()
{
  if(ServerState.NextQuantum == NULL)
  {
    ServerState.CurrentQuantum = QUANTUMFIFO_Pull();
  }
  else
  {
    ServerState.CurrentQuantum = ServerState.NextQuantum;
  }
  ServerState.NextQuantum = QUANTUMFIFO_Pull();
  
  ActualizeInterpolationData();
  
  SignalStartLoad();
}

static void SetLedStates()
{
  if(ServerState.CurrentQuantum == NULL)
  {
    //Not writing the TriLedProcess variable over
  }
  else{
    if(ServerState.InterpolationData.InterpolatorActiveInQuantum == true)
    {
      TRILED_SetLedState(TRILED_LEFT, ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[TRILED_LEFT]);
      TRILED_SetLedState(TRILED_CENTER, ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[TRILED_CENTER]);
      TRILED_SetLedState(TRILED_RIGHT, ServerState.InterpolationData.InterpolatorDummyQuantum.ledState[TRILED_RIGHT]);
    }
    else
    {
      TRILED_SetLedState(TRILED_LEFT, ServerState.CurrentQuantum->ledState[TRILED_LEFT]);
      TRILED_SetLedState(TRILED_CENTER, ServerState.CurrentQuantum->ledState[TRILED_CENTER]);
      TRILED_SetLedState(TRILED_RIGHT, ServerState.CurrentQuantum->ledState[TRILED_RIGHT]);
    }
  }
}

static inline void SynchronizeTick()
{
  ServerState.SynchronizedTickCounter = ServerState.TickCounter;
}

static void SetTickCountersToDefault()
{
  ServerState.TickCounter = TICKCOUNTER_INITVALUE;
  ServerState.SynchronizedTickCounter = TICKCOUNTER_INITVALUE;
  ServerState.Statistics.TickMargin = TICKCOUNTER_INITVALUE;
  ServerState.HMilliSecondCounter = HMSCOUNTER_INITVALUE;
}

static void SaveAndResetThreshold()
{
  if(ServerState.Statistics.MaxMarginBetweenSync < ServerState.Statistics.TickMargin)
  {
    ServerState.Statistics.MaxMarginBetweenSync = ServerState.Statistics.TickMargin;
  }
  ServerState.Statistics.TickMargin = 0;
}

void QUANTUMSERVER_Tick()
{
  if(ServerState.TickCounter != ServerState.SynchronizedTickCounter)
  {
    SynchronizeTick();
    Interpolate();
    
    if(ServerState.CurrentQuantum == NULL || GetHMilliSecondCounter() > GetLengthOfCurrQuantumInHMS())
    {
      //Because u16Properties&HOLDTIME_MASK == 0 means 0+1 * 100ms hold time
      RefreshQuantumInServer();
      
      SetLedStates();
      
      //TODO: Remove following
      STM_EVAL_LEDToggle(LED6);
      
      SetTickCountersToDefault();
    }
    else
    {
      if(ServerState.InterpolationData.InterpolatorActiveInQuantum == true)
      {
        SetLedStates();
      }
    }
    
    SaveAndResetThreshold();
  }
  else
  {
    ServerState.Statistics.TickMargin++;
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
}

QUANTUM* QUANTUMSERVER_GetCurrentQuantum()
{
  return ServerState.CurrentQuantum;
}