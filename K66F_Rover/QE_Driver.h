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

#define FREQUENCY	100

typedef struct Quadrature{
	uint16_t ticks1;
	uint16_t ticks2;
	int64_t steps;
	float32_t omega;
	} QuadratureEncoder;

void QEI_Init(QuadratureEncoder * QEI_L, uint8_t n);
void QEL_Init(QuadratureEncoder * QEI_L);
void QER_Init(QuadratureEncoder * QEI_R);
void QEI_Process(QuadratureEncoder * QEI, uint8_t timer);
void QEL_Process(QuadratureEncoder * QEI_L);
void QER_Process(QuadratureEncoder * QEI_R);

#endif /* QE_DRIVER_H_ */
