/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * Accelerometer and Magnetometer Driver
 * May-17-2017
 * FXOS8700.c
 */
 

#include <stdint.h>
#include "MK66F18.h"                    // Device header
#include "I2C.h"
#include "FXOS8700.h"


int8_t FXOS8700CQ_Init(void){
	I2C_Init(I2C0);
	I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_CTRL_REG1,0x00);
	I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_M_CTRL_REG1,0x1F);
	I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_M_CTRL_REG2,0x20);
	I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_XYZ_DATA_CFG,0x00);
	I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_CTRL_REG1,0x1C);
	return 0;
}

