#define ARM_MATH_CM4
#include "MK66F18.h"                    // Device header
#include "arm_math.h"                   // ARM::CMSIS:
#include "LEDs.h"
#include "QE_Driver.h"
#include "PIT.h"

/*
ADCC trigger enabled and sources on SIM->SOPT7 
*/

uint16_t ticks1 = 0;
uint16_t ticks2 = 0;
int64_t steps = 0;
uint8_t flag1 = 0;
uint8_t flag2 = 0;
volatile uint8_t TOF;
volatile uint8_t TOFDIR;
volatile uint8_t QUADIR;

QuadratureEncoder QEI_L;
QuadratureEncoder QEI_R;

int main(void){
	
	SystemCoreClockUpdate();
	LEDs_Init();
	//QEL_Init(&QEI_L);
	//QER_Init(&QEI_R);
	//ticks1 = FTM1->CNT;
	//steps = ticks1;
	QEI_Init(&QEI_L,1);
	QEI_Init(&QEI_R,2);
	PIT_Init(10);
	
	while(1){
		steps = QEI_L.steps;
	}
}

void PIT0_IRQHandler(void){
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	LED_Toggle(1);
	QEI_Process(&QEI_L,1);
	QEI_Process(&QEI_R,2);
	/*TOF = (FTM1->SC & FTM_SC_TOF_MASK)>>7;
  TOFDIR = (FTM1->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)>>1;
	QUADIR = (FTM1->QDCTRL & FTM_QDCTRL_QUADIR_MASK)>>2;
	ticks2 = FTM1->CNT;
	if((FTM1->SC & FTM_SC_TOF_MASK)){
		FTM1->SC &= ~(FTM_SC_TOF_MASK);
		if(!(FTM1->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&!(FTM1->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			steps += ticks2 - ticks1 - 0x10000;
		if((FTM1->QDCTRL & FTM_QDCTRL_TOFDIR_MASK)&&(FTM1->QDCTRL & FTM_QDCTRL_QUADIR_MASK)) 
			steps += ticks2 - ticks1 + 0x10000;
	} else {
		steps += ticks2 - ticks1;
	}
	ticks1 = ticks2;*/
	//QEL_Process(&QEI_L);
	//QER_Process(&QEI_R);
}
