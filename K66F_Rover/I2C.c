/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * I2C Driver
 * May-15-2017
 * I2C.c
 */

#include <stdint.h>
#include "MK66F18.h"                    // Device header
#include "I2C.h"

void I2C_Init(I2C_MemMapPtr p){
	if (p == I2C0){																		// IMU (FXOS8700 + FXAS21002)
		SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
		//SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK + SIM_SCGC5_PORTC_MASK + SIM_SCGC5_PORTD_MASK;
		//PORTD->PCR[8] |= PORT_PCR_MUX(2);
		//PORTD->PCR[9] |= PORT_PCR_MUX(2);
		//PORTA->PCR[29]|= PORT_PCR_ISF_MASK + PORT_PCR_MUX(0x01) + PORT_PCR_IRQC(0x0A);	//FXAS21002 INT1
		//PORTC->PCR[17]|= PORT_PCR_ISF_MASK + PORT_PCR_MUX(0x01) + PORT_PCR_IRQC(0x0A);	//FXOS8700 INT1
		
		//SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
		//PORTE->PCR[24] |= PORT_PCR_MUX(5);
		//PORTE->PCR[25] |= PORT_PCR_MUX(5);
		
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
		PORTB->PCR[2] |= PORT_PCR_MUX(2);
		PORTB->PCR[3] |= PORT_PCR_MUX(2);
	}
  if (p == I2C1){																		// Audio CODEC (DA7212)
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
		SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
		PORTC->PCR[10] |= PORT_PCR_MUX(2);
		PORTC->PCR[11] |= PORT_PCR_MUX(2);
	}
  p->F = I2C_F_ICR(0x2a);														// Baudrate 400k 0x17 100k ok->0x2a 
	p->C1 = I2C_C1_IICEN_MASK;												// I2C enable
}

void I2C_Deinit(I2C_MemMapPtr p){
	p->C1 = 0x00;
	if (p == I2C0) SIM->SCGC4 &= ~SIM_SCGC4_I2C0_MASK;
	if (p == I2C1) SIM->SCGC4 &= ~SIM_SCGC4_I2C1_MASK;	
}

void I2C_Start(I2C_MemMapPtr p){
	I2C_SetTX(p);
	p->C1 |= I2C_C1_MST_MASK;					// TX and master mode, Start signal when MST changes from 0 to 1.
}

void I2C_Stop(I2C_MemMapPtr p){
  p->C1 &= ~(I2C_C1_MST_MASK);			// RX and slave mode, Stop signal when MST changes from 1 to 0.
	I2C_SetRX(p);
}

void I2C_SetTX(I2C_MemMapPtr p){
	p->C1 |= I2C_C1_TX_MASK;
}

void I2C_SetRX(I2C_MemMapPtr p){
	p->C1 &= ~I2C_C1_TX_MASK;
}

void I2C_SendNACK(I2C_MemMapPtr p){
	p->C1 |= I2C_C1_TXAK_MASK;
}

void I2C_SendACK(I2C_MemMapPtr p){
	p->C1 &= ~I2C_C1_TXAK_MASK;
}

void I2C_RepeatedStart(I2C_MemMapPtr p){
	p->C1 |= I2C_C1_RSTA_MASK;
}

void I2C_WriteByte(I2C_MemMapPtr p, uint8_t data){
	p->D = data;
}

uint8_t I2C_ReadByte(I2C_MemMapPtr p){
	return p->D;
}

void I2C_Wait(I2C_MemMapPtr p){
	while((p->S & I2C_S_IICIF_MASK)==0);
	p->S |= I2C_S_IICIF_MASK;
}

uint8_t I2C_GetACK(I2C_MemMapPtr p){
	if((p->S & I2C_S_RXAK_MASK) == 0) return 1;
	else return 0;
}

void Pause(uint16_t n){
	uint16_t i;
	for(i=1;i<n;i++) {
		__asm("nop");
	}
}

void I2C_WriteReg(I2C_MemMapPtr p, uint8_t dev_addr, uint8_t addr, uint8_t data){
	I2C_Start(p);
	p->D = (dev_addr)|I2C_WRITE;
	I2C_Wait(p);
	
	p->D = addr;
	I2C_SendACK(p);
	I2C_Wait(p);
	
	p->D = data;
	I2C_SendACK(p);
	I2C_Wait(p);
	
	I2C_Stop(p);
	Pause(350);
}

uint8_t I2C_ReadReg(I2C_MemMapPtr p, uint8_t dev_addr, uint8_t addr){
	uint8_t result;
	I2C_Start(p);
	p->D = (dev_addr)|I2C_WRITE;
	I2C_Wait(p);
	
	p->D = addr;
	I2C_Wait(p);
	
	I2C_RepeatedStart(p);
	
	p->D = (dev_addr)|I2C_READ;
	I2C_Wait(p);
	
	I2C_SetRX(p);
	I2C_SendNACK(p);
	
	result = p->D;
	I2C_Wait(p);
	I2C_Stop(p);
	result = p->D;
	Pause(350);
	return result;
}

void I2C_ReadMultipleRegs(I2C_MemMapPtr p, uint8_t dev_addr, uint8_t addr, uint8_t n, uint8_t *result){
	uint8_t i;
	
	I2C_Start(p);
	p->D = dev_addr;
	I2C_Wait(p);
	
	p->D = addr;
	I2C_Wait(p);
	
	I2C_RepeatedStart(p);
	
	p->D = (dev_addr)|I2C_READ;
	I2C_Wait(p);
	
	I2C_SetRX(p);
	I2C_SendACK(p);
	
	i = p->D;
	I2C_Wait(p);
	
	for(i=0; i<n-2; i++){
		*result = p->D;
		result++;
		I2C_Wait(p);
	}
	
	I2C_SendNACK(p);
	*result = p->D;
	result++;
	I2C_Wait(p);
	I2C_Stop(p);
	*result = p->D;
	Pause(350);
}
