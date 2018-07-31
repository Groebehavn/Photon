#ifndef _QUANTUMSERVER_H_
#define _QUANTUMSERVER_H_

#define PROGRAM1_BASE                   0x08010000
#define HOLDTIME_MASK                   0x7FFF
#define INTERPOLATION_MASK              0x8000
#define INTERPOLATORACTIVE_INITVALUE    {false,{false,false,false},{false,false,false},{false,false,false},0,{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0}}
#define TICKCOUNTER_INITVALUE           0
#define STATISTICS_INITVALUE            {0,0}
#define HMSCOUNTER_INITVALUE            0
#define CURRQUANTUM_INITVALUE           0
#define NEXTQUANTUM_INITVALUE           0

typedef struct t_sQSERVER_INTERPOLATION
{
  bool InterpolatorActiveInQuantum;
  bool IncrementRed[3];
  bool IncrementGreen[3];
  bool IncrementBlue[3];
  U16 TickPeriod;
  double DeltaR[3];
  double DeltaG[3];
  double DeltaB[3];
  double CummulativeR[3];
  double CummulativeG[3];
  double CummulativeB[3];
  QUANTUM InterpolatorDummyQuantum;
}QSERVER_INTERPOLATION;

typedef struct t_sQSERVER_STATISTICS
{
  U16 TickMargin;
  U16 MaxMarginBetweenSync;
}QSERVER_STATISTICS;

typedef struct t_sQSERVER_STATE
{
  U16 TickCounter;
  U16 SynchronizedTickCounter;
  U16 HMilliSecondCounter;
  QSERVER_STATISTICS Statistics;
  QUANTUM* CurrentQuantum;
  QUANTUM* NextQuantum;
  QSERVER_INTERPOLATION InterpolationData;
}QSERVER_STATE;

//TODO: Csúszóablakos átlag a margin-ra egy új structba, csak ahhoz sok mindent kell tárolni.

void QUANTUMSERVER_DisableModule();
void QUANTUMSERVER_EnableModule();
void QUANTUMSERVER_Initialize();
QUANTUM* QUANTUMSERVER_GetCurrentQuantum();
void QUANTUMSERVER_IncrementTickCounter();
void QUANTUMSERVER_PushProgramToFifo(U8 u8Position);
void QUANTUMSERVER_Tick();

#endif