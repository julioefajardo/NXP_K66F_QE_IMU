#define ARM_MATH_CM4
#include "MK66F18.h"                    // Device header
#include "arm_math.h"                   // ARM::CMSIS:
#include "LEDs.h"
#include "QE_Driver.h"
#include "Motor_Driver.h"
#include "PIT.h"

/*
ADCC trigger enabled and sources on SIM->SOPT7 
*/

#define PID_L_KP       	0.275f               /* Proporcional */ //0.175
#define PID_L_KI       	0.0f                 /* Integral     */
#define PID_L_KD       	0.0f                 /* Derivative   */

#define PID_R_KP       	0.275f               /* Proporcional */ 
#define PID_R_KI       	0.0f                 /* Integral     */
#define PID_R_KD       	0.0f                 /* Derivative   */

#define Left_SP	     		5.0f
#define Right_SP   			5.0f

float32_t Left_error = 0.0f;
float32_t Right_error = 0.0f;

float32_t L_Motor = 0.0f;
float32_t R_Motor = 0.0f;
float32_t pwm1 = 0.25f;
float32_t pwm2 = -0.25f;

int64_t steps = 0;
float32_t omega = 0.0f;

QuadratureEncoder QE_L;
QuadratureEncoder QE_R;

arm_pid_instance_f32 Left_PID;
arm_pid_instance_f32 Right_PID;
	

int main(void){
	
	//Left Motor
	Left_PID.Kp = PID_L_KP;        /* Proporcional */
	Left_PID.Ki = PID_L_KI;        /* Integral */
	Left_PID.Kd = PID_L_KD;        /* Derivative */
    
	//Right Motor
	Right_PID.Kp = PID_R_KP;        /* Proporcional */
	Right_PID.Ki = PID_R_KI;        /* Integral */
	Right_PID.Kd = PID_R_KD;        /* Derivative */
	
	LEDs_Init();
	QE_Init(&QE_L,1);
	QE_Init(&QE_R,2);
	Motor_Init(1);
	Motor_Init(2);
	PIT_Init(PIT_FREQUENCY);
	
	QE_Process(&QE_L,1);
	QE_Process(&QE_R,2);
	
	arm_pid_init_f32(&Left_PID,1);
	arm_pid_init_f32(&Right_PID,1);
	
	//Motor_Set(&pwm1,1);
	//Motor_Set(&pwm2,2);
	
	while(1){
		steps = QE_L.steps;
		omega = QE_L.omega;
	}
}

void PIT0_IRQHandler(void){
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	LED_Toggle(1);
	QE_Process(&QE_L,1);
	QE_Process(&QE_R,2);
	Left_error = QE_L.omega - Left_SP;
	Right_error = QE_R.omega - Left_SP;
	L_Motor = arm_pid_f32(&Left_PID, Left_error);
  R_Motor = arm_pid_f32(&Right_PID, Right_error);
	L_Motor = Power_Verification(&L_Motor);
	R_Motor = Power_Verification(&R_Motor);
	Motor_Set(&L_Motor,1);
	Motor_Set(&R_Motor,2);
}
