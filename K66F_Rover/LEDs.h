/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * LED Driver
 * May-09-2017
 * LEDs.h
 */
#ifndef LEDS_H_
#define LEDS_H_

#include <stdint.h>

void LEDs_Init(void);
void LED_On(uint8_t led);
void LED_Off(uint8_t led);
void LED_Toggle(uint8_t led);

#endif /* LEDS_H_ */
