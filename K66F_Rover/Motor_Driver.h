/* Universidad Galileo
 * Turing Research Lab
 * Julio E. Fajardo
 * Robotic Mobile Platform
 * CMSIS-DSP Application
 * PWM Motor Driver
 * May-19-2017
 * Motor_Driver.h
 */
 
#define ARM_MATH_CM4
#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <stdint.h>
#include <stdlib.h>
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define MOTOR_FREQ		1000

void Motor_Init(uint8_t motor);
void Motor_Set(float32_t * duty_cycle, uint8_t motor);
float32_t Power_Verification(float32_t * pid);

#endif /* MOTOR_DRIVER_H_ */
