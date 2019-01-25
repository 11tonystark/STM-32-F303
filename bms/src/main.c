
#include "stm32f30x.h"
#include "stm32f3_discovery.h"


#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_adc.h"
#include <stm32f30x_gpio.h>

void Delay (uint32_t nTime);
uint16_t ADC1ConvertedValue = 0;
uint16_t ADC1ConvertedVoltage = 0;
uint16_t calibration_value = 0;
uint32_t TimingDelay = 0;
int main(void)
{

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

		//SET GPIO PIN 13 as output
		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_15;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

		// Initialization of GPIO PORTE PIN 13
		GPIO_Init(GPIOE,&GPIO_InitStruct);


 // At this stage the microcontroller clock tree is already configured
 RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV2; // Configure the ADC clock
 RCC->AHBENR |= RCC_AHBENR_ADC12EN; // Enable ADC1 clock
 // Setup SysTick Timer for 1 µsec interrupts

 // ADC Channel configuration PC1 in analog mode
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // GPIOC Periph clock enable
  GPIOC->MODER |= 3 << (1*2); // Configure ADC Channel7 as analog input

  /* Calibration procedure */
  ADC1->CR &= ~ADC_CR_ADVREGEN;
  ADC1->CR |= ADC_CR_ADVREGEN_0; // 01: ADC Voltage regulator enabled
 // Delay(10); // Insert delay equal to 10 µs
  ADC1->CR &= ~ADC_CR_ADCALDIF; // calibration in Single-ended inputs Mode.
  ADC1->CR |= ADC_CR_ADCAL; // Start ADC calibration
  // Read at 1 means that a calibration in progress.
  while (ADC1->CR & ADC_CR_ADCAL); // wait until calibration done
  calibration_value = ADC1->CALFACT; // Get Calibration Value ADC1
  // ADC configuration
   ADC1->CFGR |= ADC_CFGR_CONT; // ADC_ContinuousConvMode_Enable
   ADC1->CFGR &= ~ADC_CFGR_RES; // 12-bit data resolution
   ADC1->CFGR &= ~ADC_CFGR_ALIGN; // Right data alignment

  /* ADC1 regular channel7 configuration */
   ADC1->SQR1 |= ADC_SQR1_SQ1_2 | ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_0; // SQ1 = 0x07, start converting ch7
   ADC1->SQR1 &= ~ADC_SQR1_L; // ADC regular channel sequence length = 0 => 1 conversion/sequence
 //  ADC1->SMPR1 |= ADC_SMPR1_SMP7_1 | ADC_SMPR1_SMP7_0; // = 0x03 => sampling time 7.5 ADC clock cycles
   ADC1->CR |= ADC_CR_ADEN; // Enable ADC1
   while(!ADC1->ISR & ADC_ISR_ADRD); // wait for ADRDY

   ADC1->CR |= ADC_CR_ADSTART; // Start ADC1 Software Conversion

  while (1)
   {
   while(!(ADC1->ISR & ADC_ISR_EOC)); // Test EOC flag
   ADC1ConvertedValue = ADC1->DR; // Get ADC1 converted data
  // ADC1ConvertedVoltage = (ADC1ConvertedValue *3300)/4096;
  if( ADC1ConvertedValue >=0)
  {
	   GPIO_SetBits(GPIOE,GPIO_Pin_8);// Compute the voltage
   }}
  }


