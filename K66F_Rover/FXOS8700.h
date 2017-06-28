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

#define FXOS8700CQ_ADDRESS  			0x1D<<1	
#define FXOS8700CQ_STATUS 				0x00
#define FXOS8700CQ_WHOAMI 				0x0D
#define FXOS8700CQ_XYZ_DATA_CFG 	0x0E
#define FXOS8700CQ_CTRL_REG1 			0x2A
#define FXOS8700CQ_M_CTRL_REG1 		0x5B
#define FXOS8700CQ_M_CTRL_REG2 		0x5C
#define FXOS8700CQ_WHOAMI_VAL 		0xC7

#define OUT_X_MSB_REG						0x01		// [7:0] are 8 MSBs of 14-bit acceleration data for X-axis 
#define OUT_X_LSB_REG         	0x02		// [7:2] are the 6 LSB of 14-bit acceleration data for X-axis
#define OUT_Y_MSB_REG         	0x03		// [7:0] are 8 MSBs of 14-bit acceleration data for Y-axis 
#define OUT_Y_LSB_REG         	0x04		// [7:2] are the 6 LSB of 14-bit acceleration data for Y-axis 
#define OUT_Z_MSB_REG         	0x05		// [7:0] are 8 MSBs of 14-bit acceleration data for Z-axis 
#define OUT_Z_LSB_REG         	0x06		// [7:2] are the 6 LSB of 14-bit acceleration data for Z-axis 

#define MOUT_X_MSB_REG			0x33		// MSB of 16-bit magnetic data for X-axis
#define MOUT_X_LSB_REG			0x34		// LSB of 16-bit magnetic data for X-axis
#define MOUT_Y_MSB_REG			0x35		// MSB of 16-bit magnetic data for Y-axis
#define MOUT_Y_LSB_REG			0x36		// LSB of 16-bit magnetic data for Y-axis
#define MOUT_Z_MSB_REG			0x37		// MSB of 16-bit magnetic data for Z-axis
#define MOUT_Z_LSB_REG			0x38		// LSB of 16-bit magnetic data for Z-axis

#define SENSITIVITY_2G		  	4096.0f
#define SENSITIVITY_4G		  	2048.0f
#define SENSITIVITY_8G		  	1024.0f
#define SENSITIVITY_MAG		  	10.0f


typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
} IMU_raw;

typedef struct{
	float32_t x;
	float32_t y;
	float32_t z;
} IMU_data;

int8_t FXOS8700CQ_Init(void);
void FXOS8700CQ_AccRead(IMU_raw *acc_raw, IMU_data *acc_data);
void FXOS8700CQ_MagRead(IMU_raw *mag_raw, IMU_data *mag_data);
#endif /* FXOS8700_H_ */
