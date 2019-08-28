/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * Quadrature Encoder Driver
 * May-15-2017
 * QE_Driver.h
 */
 
#define ARM_MATH_CM4
#ifndef QE_DRIVER_H_
#define QE_DRIVER_H_

#include <stdint.h>
#include <stdlib.h>
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define PIT_FREQUENCY	100

typedef struct Quadrature{
	uint16_t ticks1;
	uint16_t ticks2;
	int64_t steps;
	float32_t omega;
	} QuadratureDecoder;

void QD_Init(QuadratureDecoder * QD, uint8_t n);
void QD_Process(QuadratureDecoder * QD, uint8_t timer);
void QD_Reset(QuadratureDecoder * QD);

#endif /* QE_DRIVER_H_ */
