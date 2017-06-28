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

FTM_Type *QD_addr[]    = {FTM0, FTM1, FTM2};

void QD_Init(QuadratureDecoder * QD, uint8_t timer){
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
	QD_addr[timer]->MODE |= FTM_MODE_WPDIS_MASK;
	QD_addr[timer]->QDCTRL |= FTM_QDCTRL_PHAFLTREN_MASK + FTM_QDCTRL_PHBFLTREN_MASK + FTM_QDCTRL_QUADEN_MASK;	
	QD_addr[timer]->MOD = 0xFFFF;
	QD_addr[timer]->SC = FTM_SC_CLKS(0x01) + FTM_SC_PS(0x02);
	QD->ticks1 = FTM1_CNT;
	QD->steps = QD->ticks1;
}

void QD_Process(QuadratureDecoder * QD, uint8_t timer){
	volatile int64_t delta;
	QD->ticks2 = QD_addr[timer]->CNT;
	if((QD_addr[timer]->SC & FTM_SC_TOF_MASK)){
		QD_addr[timer]->SC &= ~(FTM_SC_TOF_MASK);
		if(!(QD_addr[timer]->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&!(QD_addr[timer]->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			delta = QD->ticks2 - QD->ticks1 - 0x10000;
		if((QD_addr[timer]->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&(QD_addr[timer]->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			delta = QD->ticks2 - QD->ticks1 + 0x10000;
	} else {
		delta = QD->ticks2 - QD->ticks1;
	}
	QD->steps += delta;
	QD->omega = ((delta*PI)/562.0f)/((float32_t)(1.0f/PIT_FREQUENCY));												
	QD->ticks1 = QD->ticks2;
}
