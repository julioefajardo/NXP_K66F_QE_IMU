/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * Quadrature Encoder Driver
 * May-15-2017
 * QE_Driver.c
 */

#include <stdint.h>
#include "MK66F18.h"                    // Device header
#include "QE_Driver.h"

FTM_Type *FTM_addr[]    = {FTM0, FTM1, FTM2};

void QEI_Init(QuadratureEncoder * QEI, uint8_t timer){
	switch(timer){
		case 1:{
			SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
			SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
			PORTA->PCR[8] |= PORT_PCR_MUX(0x06); 
			PORTA->PCR[9] |= PORT_PCR_MUX(0x06);		
		} break; 
		case 2:{
			SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
			SIM->SCGC6 |= SIM_SCGC6_FTM2_MASK;
			PORTB->PCR[18] |= PORT_PCR_MUX(0x06); 
			PORTB->PCR[19] |= PORT_PCR_MUX(0x06);
		} break;
	}
	FTM_addr[timer]->MODE |= FTM_MODE_WPDIS_MASK;
	FTM_addr[timer]->QDCTRL |= FTM_QDCTRL_PHAFLTREN_MASK + FTM_QDCTRL_PHBFLTREN_MASK + FTM_QDCTRL_QUADEN_MASK;	
	FTM_addr[timer]->MOD = 0xFFFF;
	FTM_addr[timer]->SC = FTM_SC_CLKS(0x01) + FTM_SC_PS(0x05);
	QEI->ticks1 = FTM1_CNT;
	QEI->steps = QEI->ticks1;
}

void QEI_Process(QuadratureEncoder * QEI, uint8_t timer){
	volatile int64_t delta;
	QEI->ticks2 = FTM_addr[timer]->CNT;
	if((FTM_addr[timer]->SC & FTM_SC_TOF_MASK)){
		FTM_addr[timer]->SC &= ~(FTM_SC_TOF_MASK);
		if(!(FTM_addr[timer]->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&!(FTM_addr[timer]->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			delta = QEI->ticks2 - QEI->ticks1 - 0x10000;
		if((FTM_addr[timer]->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&(FTM_addr[timer]->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			delta = QEI->ticks2 - QEI->ticks1 + 0x10000;
	} else {
		delta = QEI->ticks2 - QEI->ticks1;
	}
	QEI->steps += delta;
	QEI->omega = ((delta*PI)/84.0f)/((float32_t)(1.0f/FREQUENCY));												//168 steps per revolute
	QEI->ticks1 = QEI->ticks2;
}
