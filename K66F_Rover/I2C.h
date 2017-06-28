/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * I2C Driver
 * May-17-2017
 * I2C.h
 */
#ifndef I2C_H_
#define I2C_H_

#include "MK66F18.h"                    // Device header
#include <stdint.h>


#define 		I2C_WRITE 			0
#define 		I2C_READ 				1

void I2C_Init(I2C_MemMapPtr p);
void I2C_Deinit(I2C_MemMapPtr p);
void I2C_Start(I2C_MemMapPtr p);
void I2C_Stop(I2C_MemMapPtr p);
void I2C_SetTX(I2C_MemMapPtr p);
void I2C_SetRX(I2C_MemMapPtr p);
void I2C_SendNACK(I2C_MemMapPtr p);
void I2C_SendACK(I2C_MemMapPtr p);
void I2C_RepeatedStart(I2C_MemMapPtr p);
void I2C_WriteByte(I2C_MemMapPtr p, uint8_t data);
uint8_t I2C_ReadByte(I2C_MemMapPtr p);
void I2C_Wait(I2C_MemMapPtr p);
uint8_t I2C_GetACK(I2C_MemMapPtr p);
void Pause(uint16_t n);
void I2C_WriteReg(I2C_MemMapPtr p, uint8_t dev_addr, uint8_t addr, uint8_t data);
uint8_t I2C_ReadReg(I2C_MemMapPtr p, uint8_t dev_addr, uint8_t addr);
void I2C_ReadMultipleRegs(I2C_MemMapPtr p, uint8_t dev_addr, uint8_t addr, uint8_t n, uint8_t * res);
#endif /* I2C_H_ */
