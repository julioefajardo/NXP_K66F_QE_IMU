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
	if(I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_WHOAMI) == FXOS8700CQ_WHOAMI_VAL){
		I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_CTRL_REG1,0x00);
		I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_M_CTRL_REG1,0x1F);
		I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_M_CTRL_REG2,0x20);
		I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_XYZ_DATA_CFG,0x01);
		I2C_WriteReg(I2C0,FXOS8700CQ_ADDRESS,FXOS8700CQ_CTRL_REG1,0x0D);
		return 0;
	} else return -1;
}

void FXOS8700CQ_AccRead(IMU_raw *acc_raw, IMU_data *acc_data){
	acc_raw->x = (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,OUT_X_LSB_REG)>>2);
	acc_raw->x |= (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,OUT_X_MSB_REG)<<8);
	
	acc_raw->y = (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,OUT_Y_LSB_REG)>>2);
	acc_raw->y |= (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,OUT_Y_MSB_REG)<<8);
	
	acc_raw->z = (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,OUT_Z_LSB_REG)>>2);
	acc_raw->z |= (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,OUT_Z_MSB_REG)<<8);
	
	acc_data->x = (float32_t)(acc_raw->x/SENSITIVITY_2G);
	acc_data->y = (float32_t)(acc_raw->y/SENSITIVITY_2G);
	acc_data->z = (float32_t)(acc_raw->z/SENSITIVITY_2G);
}

void FXOS8700CQ_MagRead(IMU_raw *mag_raw, IMU_data *mag_data){
	mag_raw->x = I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,MOUT_X_LSB_REG);
	mag_raw->x |= (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,MOUT_X_MSB_REG)<<8);
	
	mag_raw->y = I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,MOUT_Y_LSB_REG);
	mag_raw->y |= (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,MOUT_Y_MSB_REG)<<8);
	
	mag_raw->z = I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,MOUT_Z_LSB_REG);
	mag_raw->z |= (I2C_ReadReg(I2C0,FXOS8700CQ_ADDRESS,MOUT_Z_MSB_REG)<<8);
	
	mag_data->x = (float32_t)(mag_raw->x/SENSITIVITY_MAG);
	mag_data->y = (float32_t)(mag_raw->y/SENSITIVITY_MAG);
	mag_data->z = (float32_t)(mag_raw->z/SENSITIVITY_MAG);
}
