#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

//TODO: Ez csak tipp, ennyi kb. eleg, kesobb le lehet venni minimumra
#define USART_MESSAGE_SIZE 32

typedef __packed struct t_sUSART_MESSAGE
{
  U8 u8Characters[USART_MESSAGE_SIZE];
}USART_MESSAGE;

typedef struct t_sCOMM_STATE
{
  bool bMessageReceived;
  bool bMessageProcessing;
  USART_MESSAGE sMessage;
}COMM_STATE;

void COMMUNICATION_Initialize();
void COMMUNICATION_Tick();

#endif