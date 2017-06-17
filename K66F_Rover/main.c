#define ARM_MATH_CM4
#include "MK66F18.h"                    // Device header
#include "arm_math.h"                   // ARM::CMSIS:
#include "LEDs.h"
#include "QE_Driver.h"
#include "PIT.h"

/*
ADCC trigger enabled and sources on SIM->SOPT7 
*/

int64_t steps = 0;
float32_t omega = 0.0f;
QuadratureEncoder QEI_L;
QuadratureEncoder QEI_R;

int main(void){
	
	SystemCoreClockUpdate();
	LEDs_Init();
	QEI_Init(&QEI_L,1);
	QEI_Init(&QEI_R,2);
	PIT_Init(FREQUENCY);
	
	QEI_Process(&QEI_L,1);
	QEI_Process(&QEI_R,2);
	
	while(1){
		steps = QEI_L.steps;
		omega = QEI_L.omega;
	}
}

void PIT0_IRQHandler(void){
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	LED_Toggle(1);
	QEI_Process(&QEI_L,1);
	QEI_Process(&QEI_R,2);
}
