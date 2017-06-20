/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * Accelerometer and Magnetometer Driver
 * May-17-2017
 * FXOS8700.h
 */

#define ARM_MATH_CM4

#ifndef FXOS8700_H_
#define FXOS8700_H_

#include "MK66F18.h"                    // Device header
#include <stdint.h>
#include "arm_math.h"                   // ARM::CMSIS:
#include "I2C.h"

#define FXOS8700CQ_ADDRESS  			0x1F<<1	
#define FXOS8700CQ_STATUS 				0x00
#define FXOS8700CQ_WHOAMI 				0x0D
#define FXOS8700CQ_XYZ_DATA_CFG 	0x0E
#define FXOS8700CQ_CTRL_REG1 			0x2A
#define FXOS8700CQ_M_CTRL_REG1 		0x5B
#define FXOS8700CQ_M_CTRL_REG2 		0x5C
#define FXOS8700CQ_WHOAMI_VAL 		0xC4

#define FXOS8700CQ_READ_LEN 			13

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
} SRAWDATA;

int8_t FXOS8700CQ_Init(void);

#endif /* FXOS8700_H_ */
