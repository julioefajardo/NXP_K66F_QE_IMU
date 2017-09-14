/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * UART Driver
 * May-27-2017
 * UART.c
 */
 
#include <stdint.h>
#include "MK66F18.h"                    // Device header
#include "UART.h"
 
void UART_Init(uint32_t baudrate){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; 
	PORTB->PCR[16] = (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_PFE_MASK | PORT_PCR_MUX(3));
	PORTB->PCR[17] = (PORT_PCR_DSE_MASK  | PORT_PCR_SRE_MASK | PORT_PCR_MUX(3));
	UART0->C2 &= (uint8_t)~(uint8_t)((UART_C2_TE_MASK | UART_C2_RE_MASK));
	UART0->BDH = UART_BDH_SBR(0x00);																																			// 115200 Bauds	
	UART0->BDL = UART_BDL_SBR(0x46);	
	UART0->C4 = UART_C4_BRFA(0x10);
	UART0->C1 = UART_C1_ILT_MASK;
	UART0->C2 = (UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK);
	NVIC_EnableIRQ(UART0_RX_TX_IRQn);
}
	
void UART_Send(char dato){
	while (!((UART0->S1)&(UART_S1_TDRE_MASK)));  
	UART0->D = dato;
}

void UART_PutString(char *mystring){
	while(*mystring){
		UART_Send(*mystring);
		mystring++;
	}
}

