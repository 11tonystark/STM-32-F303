#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_adc.h"
#include <stm32f30x_gpio.h>

int  calvalue=0;


int main(void)
{



 RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV2;
 RCC->AHBENR |= RCC_AHBENR_ADC12EN; //  ADC1 clock

 	// Initialization of GPIO PORTE PIN 13
 //	GPIO_Init(GPIOE,&GPIO_InitStruct);


 //gpio set for adcccccc
 //Enable clock for GPIOE
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);

 	//SET GPIO PIN 1c as analog
 	GPIO_InitTypeDef GPIO_InitStruct;
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
 	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

 	GPIO_Init(GPIOC,&GPIO_InitStruct);
// step pwm pin
	GPIO_InitTypeDef            GPIO_InitStructure;				//structure for GPIO setup
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;			//structure for TIM Time Base
	TIM_OCInitTypeDef			TIM_OCInitStructure;			//structure for TIM Output Compare

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);			//enable the AHB Peripheral Clock to use GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		//enable the TIM1 clock

	/* Pin configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_2);


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

	//SET GPIO PIN 13 as output
	//GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_11|GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	// Initialization of GPIO PORTE PIN 13
	GPIO_Init(GPIOE,&GPIO_InitStruct);



	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_Period = 49;	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);							//enable the PWM output
	TIM_Cmd(TIM1, ENABLE);



 	// set adc
  ADC1->CR &= ~ADC_CR_ADVREGEN;
  ADC1->CR |= ADC_CR_ADVREGEN_0;
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  ADC1->CR &= ~ADC_CR_ADCALDIF;
  ADC1->CR |= ADC_CR_ADCAL;

  while (ADC1->CR & ADC_CR_ADCAL); // wait until calibration done just like usart

  ADC1->CFGR |= ADC_CFGR_CONT;
  ADC1->CFGR &= ~ADC_CFGR_RES; // 12-bit data resolution
  ADC1->CFGR &= ~ADC_CFGR_ALIGN;


  ADC1->SQR1 |= ADC_SQR1_SQ1_2 | ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_0;
  ADC1->SQR1 &= ~ADC_SQR1_L;
  ADC1->SMPR1 |= ADC_SMPR1_SMP7_1 | ADC_SMPR1_SMP7_0;
  ADC1->CR |= ADC_CR_ADEN; // Enable ADC1
  ADC_Cmd(ADC1, ENABLE);
  while(!ADC1->ISR & ADC_ISR_ADRD);

  ADC1->CR |= ADC_CR_ADSTART; // most prob. adc start hoga
  int  ADCoutput=0;
  int p;

 while (1)
  {
  while(!(ADC1->ISR & ADC_ISR_EOC)); // flag
  ADCoutput= ADC1->DR; // output
  if(ADCoutput>0)
  {
	//  p=ADCoutput-1;
	  TIM_SetCompare1(TIM1,ADCoutput);
  //	GPIO_SetBits(GPIOE,GPIO_Pin_8);
  }

  }
}
