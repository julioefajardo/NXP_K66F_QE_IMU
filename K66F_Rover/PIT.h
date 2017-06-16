/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * PIT Driver
 * May-15-2017
 * LEDs.h
 */
#ifndef PIT_H_
#define PIT_H_

#include <stdint.h>
#include "MK66F18.h"                    // Device header

void PIT_Init(uint32_t frequency);

#endif /* PIT_H_ */
