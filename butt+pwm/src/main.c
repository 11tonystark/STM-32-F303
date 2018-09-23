#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>

int main(void)
{
	unsigned int input_val;
	//volatile unsigned int i=0;

	//Enable clock for both GPIOE and GPIOA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;


	GPIO_InitTypeDef            GPIO_InitStructure;				//structure for GPIO setup
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;			//structure for TIM Time Base
	TIM_OCInitTypeDef			TIM_OCInitStructure;			//structure for TIM Output Compare

	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);			//enable the AHB Peripheral Clock to use GPIOB
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

	//configuration for user button connected to PA0
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

    while(1)
    {
    	input_val = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
    	if (input_val ==1)
    		TIM_SetCompare1(TIM1,1);

    		//GPIO_SetBits(GPIOE,GPIO_Pin_9);
    	else {
    		TIM_SetCompare1(TIM1,0);


		}
    }
}
