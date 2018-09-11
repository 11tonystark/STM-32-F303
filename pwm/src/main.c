#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include "stm32f30x_tim.h"

/* #function prototypes goes here ---------- */
void PWM_Init(void);
void Delay(unsigned int);

int main(void)
{
	PWM_Init();



    while(1)
    {
    	unsigned char var=49;
    	TIM_SetCompare1(TIM1,var);



    }
}



void Delay(unsigned int n){
	unsigned int i =0;
	for ( i = 0; i < n; ++i) ;
}


void PWM_Init(void)
{
	GPIO_InitTypeDef            GPIO_InitStructure;				//structure for GPIO setup
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;			//structure for TIM Time Base
	TIM_OCInitTypeDef			TIM_OCInitStructure;			//structure for TIM Output Compare

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);			//enable the AHB Peripheral Clock to use GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		//enable the TIM1 clock

	/* Pin configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_2);


	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_Period = 49;	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);							//enable the PWM output
	TIM_Cmd(TIM1, ENABLE);
}
