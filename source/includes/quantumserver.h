#ifndef _QUANTUMSERVER_H_
#define _QUANTUMSERVER_H_

#define PROGRAM1_BASE   0x08010000
#define HOLDTIME_MASK   0x7FFF
#define BUFFERSTATE_INITVALUE   true
#define TICKCOUNTER_INITVALUE   0
#define HMSCOUNTER_INITVALUE    0
#define CURRQUANTUM_INITVALUE   0

typedef struct t_sQSERVER_STATE
{
  bool bBufferState;
  U16 TickCounter;
  U16 HMilliSecondCounter;
  QUANTUM* CurrentQuantum;
}QSERVER_STATE;

void QUANTUMSERVER_DisableModule();
void QUANTUMSERVER_EnableModule();
void QUANTUMSERVER_Initialize();
QUANTUM QUANTUMSERVER_GetCurrentQuantum();
void QUANTUMSERVER_RefreshQuantumInServer();
void QUANTUMSERVER_SetLedStates();
U16 QUANTUMSERVER_GetTickCounter();
void QUANTUMSERVER_IncrementTickCounter();
void QUANTUMSERVER_SetTickCounterToDefault();
U16 QUANTUMSERVER_GetHMilliSecondCounter();
void QUANTUMSERVER_IncrementHMilliSecondCounter();
void QUANTUMSERVER_SetHMilliSecondCounterToDefault();
void QUANTUMSERVER_PushProgramToFifo(U8 u8Position);

#endif