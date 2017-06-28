/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * UART Driver
 * May-27-2017
 * UART.h
 */
 
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "MK66F18.h"                    // Device header

void UART_Init(uint32_t baudrate);
void UART_Send(char dato);
void UART_PutString(char *mystring);

#endif /* UART_H_ */
