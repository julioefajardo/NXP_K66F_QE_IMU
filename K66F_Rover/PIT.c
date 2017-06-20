/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * PIT Driver
 * May-15-2017
 * PIT.c
 */
 
#include <stdint.h>
#include "MK66F18.h"                    // Device header
#include "PIT.h"
#include "LEDs.h"
#include "QE_Driver.h"

void PIT_Init(uint32_t frequency){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR &= ~(PIT_MCR_MDIS_MASK + PIT_MCR_FRZ_MASK);
	PIT->CHANNEL[0].LDVAL = (SystemCoreClock/4)/frequency;
	PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK + PIT_TCTRL_TEN_MASK;
	NVIC_EnableIRQ(PIT0_IRQn);
}

