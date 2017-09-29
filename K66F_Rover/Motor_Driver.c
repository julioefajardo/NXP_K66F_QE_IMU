/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * PWM Motor Driver
 * May-19-2017
 * Motor_Driver.c
 */



#include <stdint.h>
#include "MK66F18.h"                    // Device header
#include "Motor_Driver.h"

FTM_Type *MOTOR_addr[]    = {FTM3, FTM3, FTM3, FTM3};
const uint8_t channel[] = { 4, 4, 0, 0};
GPIO_Type *dir_addr[]    = { PTC, PTC, PTD, PTD };
const uint32_t dir_mask[] = { 1<<12, 1<<12,  1<<2, 1<<2 };


//PTC8  MOTOR 1 FTM3_CH4
//PTC12 MOTOR 1 DIR
//PTD0  MOTOR 2 FTM3_CH0
//PTD2  MOTOR 2 DIR

// PWM Initialization (Freq = 1 kHz), receives as argument the number of motor (1 is LEFT, 2 is RIGHT)
void Motor_Init(uint8_t motor){
	switch(motor){
		case 1:{
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
			SIM->SCGC3 |= SIM_SCGC3_FTM3_MASK;
			PORTC->PCR[8] |= PORT_PCR_MUX(0x03);
			PORTC->PCR[12]|= PORT_PCR_MUX(0x01);
			PTC->PDDR |= (1<<12);
		} break;
		case 2:{
			SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
			SIM->SCGC3 |= SIM_SCGC3_FTM3_MASK;
			PORTD->PCR[0] |= PORT_PCR_MUX(0x04);
			PORTD->PCR[2] |= PORT_PCR_MUX(0x01);
			PTD->PDDR |= (1<<2);
		} break;
	}
	MOTOR_addr[motor]->MODE |= FTM_MODE_WPDIS_MASK + FTM_MODE_INIT_MASK;
	MOTOR_addr[motor]->CONTROLS[channel[motor]].CnSC = FTM_CnSC_CHIE_MASK+FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK; // Edge Align PWM 
	MOTOR_addr[motor]->CONTROLS[channel[motor]].CnV  = FTM_CnV_VAL(0);																						// Duty Cycle = 0
	MOTOR_addr[motor]->MOD = FTM_MOD_MOD((SystemCoreClock/4)/MOTOR_FREQ);																					//(45MHz/4)/frequency
	MOTOR_addr[motor]->SC = FTM_SC_CLKS(0x01) + FTM_SC_PS(0x00);																									// SystemClock/4
}

// Set PWM to Motor Driver, receives as argument the duty cycle (between -1.0f and 1.0f) and the number of motor (1 is LEFT, 2 is RIGHT) 
void Motor_Set(float32_t * duty_cycle, uint8_t motor){
	uint16_t value;
	if((*duty_cycle)<0) {
		dir_addr[motor]->PCOR |= dir_mask[motor];
		value = (uint16_t) (((SystemCoreClock/4)/MOTOR_FREQ)*(*duty_cycle*(-1.0f)));
	}
	else {
		dir_addr[motor]->PSOR |= dir_mask[motor];
		value = (uint16_t) (((SystemCoreClock/4)/MOTOR_FREQ)*(*duty_cycle));
	}
	MOTOR_addr[motor]->CONTROLS[channel[motor]].CnV  = FTM_CnV_VAL(value);
}

// Keep the PID Output between -1.0f and 1.0f.
float32_t Power_Verification(float32_t * pid){
	if(*pid>=0.0f){
		if(*pid>1.0f) return 1.0f;
		else if(*pid<0.05f) return 0.0f;
		else return *pid;
	}
	else{
		if(*pid<-1.0f) return -1.0f;
		else if(*pid>-0.05f) return 0.0f;
		else return *pid;
	}
}
