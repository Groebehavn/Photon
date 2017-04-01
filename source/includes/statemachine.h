#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

typedef __packed struct t_sSYSTEMSTATE
{
  bool bRecievedData;
  bool bLoadInitialize;
  bool bLoadNewProgram;
}SYSTEMSTATE;

void SYS_SetLoadInitialize();
void SYS_SetStartLoad();
void SYS_SetRecievedData();
void SYS_ResetLoadInitialize();
void SYS_ResetStartLoad();
void SYS_ResetRecievedData();
bool SYS_GetLoadInitialize();
bool SYS_GetStartLoad();
bool SYS_GetRecievedData();

#endif