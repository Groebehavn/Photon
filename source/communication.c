#include "headers.h"

static COMM_STATE commState;

static TM_USB_VCP_Result CheckConnection()
{
  if(TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED)
  {
    /* Turn on GREEN led */
    STM_EVAL_LEDOn(LED4);
    STM_EVAL_LEDOff(LED5);
    
    return TM_USB_VCP_CONNECTED;
  }
  else
  {
    STM_EVAL_LEDOn(LED5);
    STM_EVAL_LEDOff(LED4);
  }
  
  return TM_USB_VCP_NOT_CONNECTED;
}
static U8 u8Data = 0x0;
static TM_USB_VCP_Result GetMessage()
{
  
  if(TM_USB_VCP_Gets((char*)commState.sMessage.u8Characters,USART_MESSAGE_SIZE) == 0)
  {
    return TM_USB_VCP_DATA_EMPTY;
  }
  
  return TM_USB_VCP_DATA_OK;
}

static void ProcessMessage()
{
  TM_USB_VCP_Send(commState.sMessage.u8Characters,32);
}

void COMMUNICATION_Initialize()
{
  commState.bMessageReceived = false;
  commState.bMessageProcessing = false;
  TM_USB_VCP_Init();
}

void COMMUNICATION_Tick()
{
  if(CheckConnection() == TM_USB_VCP_NOT_CONNECTED)
  {
    return;
  }
  
  if(GetMessage() == TM_USB_VCP_DATA_OK)
  {
    ProcessMessage();
  }
}