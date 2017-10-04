#define ARM_MATH_CM4
#if !defined  (__FPU_PRESENT) 
  #define __FPU_PRESENT             1       
#endif 

#include <stdio.h>
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "MK66F18.h"                    // Device header
#include "LEDs.h"
#include "QE_Driver.h"
#include "Motor_Driver.h"
#include "PIT.h"
#include "FXOS8700.h"
#include "I2C.h"
#include "UART.h"

/*
ADCC trigger enabled and sources on SIM->SOPT7 
*/

// PID Constants
#define PID_L_KP       	0.275f     		          	
#define PID_L_KI       	0.025f      	         	
#define PID_L_KD       	0.5f                 		

#define PID_R_KP       	0.275f               			
#define PID_R_KI       	0.025f               		
#define PID_R_KD       	0.5f                 		

// Fixed Set Point
//#define Left_SP	     		-3.5f
//#define Right_SP   			-3.5f

// Angular Velocities SP 
float32_t Left_SP = 0.0f;
float32_t Right_SP = 0.0f;

// Angular Velocities error
float32_t Left_error = 0.0f;
float32_t Right_error = 0.0f;

// Motor Power (PWM output - between -1.0f and 1.0f)
float32_t L_Motor = 0.0f;
float32_t R_Motor = 0.0f;

// Quadrature Decoder Structures
QuadratureDecoder QD_L;
QuadratureDecoder QD_R;

// CMSIS-DSP PID instances for Left and Right Wheels
arm_pid_instance_f32 Left_PID;
arm_pid_instance_f32 Right_PID;

// Aux variables
uint8_t num = 0;
uint8_t i = 0;

// Debugging
char string[24];

// Parse variables
char num1[8];
char num2[8];
uint8_t data_ready;
int16_t omega_a = 0;
int16_t omega_b = 0;


int main(void){
		
  // Left Motor PID Definitions
  Left_PID.Kp = PID_L_KP;        /* Proporcional */
  Left_PID.Ki = PID_L_KI;        /* Integral */
  Left_PID.Kd = PID_L_KD;        /* Derivative */
    
  // Right Motor PID Definitions
  Right_PID.Kp = PID_R_KP;        /* Proporcional */
  Right_PID.Ki = PID_R_KI;        /* Integral */
  Right_PID.Kd = PID_R_KD;        /* Derivative */
	
	// Hardware Initialization
  LEDs_Init();
  QD_Init(&QD_L,1);
  QD_Init(&QD_R,2);
  Motor_Init(1);
  Motor_Init(2);
  UART_Init(115200);
  PIT_Init(PIT_FREQUENCY);
  SysTick_Config(SystemCoreClock/20);
	
  // Quadrature Decoding Process Initialization
  QD_Process(&QD_L,1);
  QD_Process(&QD_R,2);
	
  // PID Initialization
  arm_pid_init_f32(&Left_PID,1);
  arm_pid_init_f32(&Right_PID,1);
	
  while(1){
	  if(data_ready){
		  omega_a = atoi(num1);
		  omega_b = atoi(num2);
		  Left_SP = omega_a/(100.0f);
		  Right_SP = omega_b/(100.0f);
		  if (omega_a > 123) LED_On(0);
		  else LED_Off(0);
		  if (omega_b > 123) LED_On(2);
		  else LED_Off(2);
		  data_ready = 0;
	  } 
  }
}


// Debugging through UART 
void SysTick_Handler(void){
  LED_Toggle(1);
  sprintf(string,"%.2f,\t%.2f,\t%.2f,\t%.2f\r",Left_SP,QD_L.omega,Right_SP,QD_R.omega);
  //UART_PutString(string);
}


// Angular Velocity Controller
void PIT0_IRQHandler(void){
  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;																										// Clear Flag
  QD_Process(&QD_L,1);																																					// Quadrature Decoder Processing
  QD_Process(&QD_R,2);
  Left_error = Left_SP - QD_L.omega;																														// Error
  Right_error = Right_SP - QD_R.omega;
  L_Motor = ((Left_SP>=-0.01f)&&(Left_SP<=0.01f))?0.0f:arm_pid_f32(&Left_PID, Left_error);			// PID Output
  R_Motor = ((Right_SP>=-0.01f)&&(Right_SP<=0.01f))?0.0f:arm_pid_f32(&Right_PID, Right_error);
  L_Motor = Power_Verification(&L_Motor);																												// Power Verification (Between -1.0f and 1.0f)
  R_Motor = Power_Verification(&R_Motor);
  Motor_Set(&L_Motor,1);																																				// Set PWM to Motor Driver
  Motor_Set(&R_Motor,2);
}

// UART Data Parser (Parse data from ROSSERIAL)
void UART0_RX_TX_IRQHandler(void){
  volatile uint8_t data ;
  (void)UART0->S1;
  data = UART0->D;
  switch(num){
	  case 0:{
		  data_ready = 0;
		  if(data != ','){
			  if((data>='0')&&(data<='9')){
				  num1[i] = data;
				  i++;
			  } else {
				  if(data=='-'){
					  num1[i] = data;
					  i++;
				  }
			  }
		  } else{
			  num1[i] = '\0';
			  num = 1;
			  i = 0;
		  }
	  } break;
	  case 1:{
		  data_ready = 0;
		  if(data != '*'){
			  num2[i] = data;
			  i++;
		  } else{
			  num2[i] = '\0';
			  num = 2;
			  i = 0;
		  }
	  } break;
	  case 2:{
		  data_ready = 1;
		  num = 0;
	  } break;
  }
}
