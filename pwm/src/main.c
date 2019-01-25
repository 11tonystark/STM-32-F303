#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include "stm32f30x_tim.h"

/* #function prototypes goes here ---------- */
void PWM_Init(void);




int main(void)
{
	PWM_Init();



    while(1)
    {

    	int x;
    	x=2400;
    	GPIO_SetBits(GPIOE,GPIO_Pin_13);
    			TIM_SetCompare2(TIM3, x);
    			TIM_SetCompare4(TIM1, x);





    }
}



void PWM_Init(void)
{//structure for GPIO setup
	GPIO_InitTypeDef            GPIO_InitStructure;
	//structure for TIM Time Base
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
	//structure for TIM Output Compare
	TIM_OCInitTypeDef			TIM_OCInitStructure;

	//enable the AHB Peripheral Clock to use GPIOE
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	//enable the TIM1 and 3 clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// Pin configuration of PWM
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_2);//Right front
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_2);//Left front
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_2);//Right back
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_2);//Left back

	TIM_TimeBaseStructure.TIM_Period = 4800-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);//For GPIOE 9,11
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//For GPIOE 6,7

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 4799;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	//enable the PWM output
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);

	TIM_SetCompare1(TIM1, 0);
	TIM_SetCompare2(TIM1, 0);

	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	TIM_SetCompare1(TIM3, 0);
	TIM_SetCompare2(TIM3, 0);

}

