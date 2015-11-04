#ifndef _TRILEDDRIVER_H_
#define _TRILEDDRIVER_H_

void TRILEDDRIVER_TurnOffAll(void);
void TRILEDDRIVER_TurnOn(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color);
void TRILEDDRIVER_TurnOff(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color);
void TRILEDDRIVER_Toggle(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color);
void TRILEDDRIVER_ProgressSpecificLedHandler(TRILED_DESCRIPTOR descriptor, TRILED_COLOR color);

#endif