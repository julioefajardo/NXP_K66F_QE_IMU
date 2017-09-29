/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * LED Driver
 * May-15-2017
 * LEDs.c
 */

#include <stdint.h>
#include "MK66F18.h"                    // Device header
#include "LEDs.h"

GPIO_Type *leds_addr[]    = { PTC, PTE, PTA };
const uint32_t leds_mask[] = { 1<<9, 1<<6,  1<<11 };
	
// RGB LED Initialization
void LEDs_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK + SIM_SCGC5_PORTC_MASK + SIM_SCGC5_PORTE_MASK;
	PORTA->PCR[11] |= PORT_PCR_MUX(0x01);
	PORTC->PCR[9] |= PORT_PCR_MUX(0x01);
	PORTE->PCR[6] |= PORT_PCR_MUX(0x01);
	PTA->PDDR |= (1<<11);
	PTC->PDDR |= (1<<9);
	PTE->PDDR |= (1<<6);
	PTA->PSOR |= (1<<11);
	PTC->PSOR |= (1<<9);
	PTE->PSOR |= (1<<6);
}

// Turn ON LED, receives as argument the led number (0 is R, 1 is G and 2 is B)
void LED_On(uint8_t led){
	leds_addr[led]->PCOR |= leds_mask[led];
}

// Turn OFF LED, receives as argument the led number (0 is R, 1 is G and 2 is B)
void LED_Off(uint8_t led){
	leds_addr[led]->PSOR |= leds_mask[led];
}

// LED Toogle, receives as argument the led number (0 is R, 1 is G and 2 is B)
void LED_Toggle(uint8_t led){
	leds_addr[led]->PTOR |= leds_mask[led];
}
