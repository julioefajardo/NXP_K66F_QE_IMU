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

// Quadrature Decoder Initialization, receives as argument a QuadratureDecoder structure (ticks, steps, omega)
// and the number of the motor encoder to use
void QD_Init(QuadratureDecoder * QD, uint8_t encoder){
	switch(encoder){
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
	QD_addr[encoder]->MODE |= FTM_MODE_WPDIS_MASK;
	QD_addr[encoder]->QDCTRL |= FTM_QDCTRL_PHAFLTREN_MASK + FTM_QDCTRL_PHBFLTREN_MASK + FTM_QDCTRL_QUADEN_MASK;	
	QD_addr[encoder]->MOD = 0xFFFF;
	QD_addr[encoder]->SC = FTM_SC_CLKS(0x01) + FTM_SC_PS(0x00);
	QD->ticks1 = FTM1_CNT;
	QD->steps = QD->ticks1;
}

// Quadrature Decoder Process, receives as argument a QuadratureDecoder structure and the number of the motor encoder to use, 
// it determines the amount of steps (64 bit signed) and the angular velocity of the motor (5400 steps per revolution).
void QD_Process(QuadratureDecoder * QD, uint8_t encoder){
	volatile int64_t delta;
	QD->ticks2 = QD_addr[encoder]->CNT;
	if((QD_addr[encoder]->SC & FTM_SC_TOF_MASK)){
		QD_addr[encoder]->SC &= ~(FTM_SC_TOF_MASK);
		if(!(QD_addr[encoder]->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&!(QD_addr[encoder]->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			delta = QD->ticks2 - QD->ticks1 - 0x10000;
		if((QD_addr[encoder]->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&(QD_addr[encoder]->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			delta = QD->ticks2 - QD->ticks1 + 0x10000;
	} else {
		delta = QD->ticks2 - QD->ticks1;
	}
	QD->steps += delta;
	QD->omega = (((float32_t)(PIT_FREQUENCY))*(delta*PI)/8100.0f); //nuevos motores
	//QD->omega = (((float32_t)(PIT_FREQUENCY))*(delta*PI)/2700.0f);	 //viejos motores
	QD->ticks1 = QD->ticks2;
}

void QD_Reset(QuadratureDecoder * QD){
	QD->ticks1 = 0; 
	QD->ticks2 = 0;
	QD->steps = 0;
	QD->omega = 0.0f;												
}

