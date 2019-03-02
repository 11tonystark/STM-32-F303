#include "stm32f30x.h"
void Delay (uint32_t nTime);
uint16_t ADC1ConvertedValue = 0;
uint16_t ADC1ConvertedVoltage = 0;
uint16_t calibration_value = 0;
volatile uint32_t TimingDelay = 0;

void Delay (uint32_t nTime)
{
 TimingDelay = nTime;
 while (TimingDelay !=0);
}
void uarttransmit(char data)
{
	USART_SendData(UART4,data);
	        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);


}

void UART_Init()
{

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	// Enable UART clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	/* UART configuration */
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* UART4 configured as follow:
					- BaudRate = speed parameter above
					- Word Length = 8 Bits
					- One Stop Bit
					- No parity
					- Hardware flow control disabled (RTS and CTS signals)
					- Receive and transmit enabled
	*/
	USART_Init(UART4, &USART_InitStructure);

	// Configure UART Tx as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// Configure UART Rx as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// Connect PC10 to UART4_Tx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_5);

	// Connect PC11 to UART4_Rx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_5);

	// Enable UART
	USART_Cmd(UART4, ENABLE);
}


int main(void)
{
	//structure for GPIO setup
		GPIO_InitTypeDef            GPIO_InitStructure;
		//structure for TIM Time Base
		TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
		//structure for TIM Output Compare
		TIM_OCInitTypeDef			TIM_OCInitStructure;

		//enable the AHB Peripheral Clock to use GPIOE
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);


		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);


		// Pin configuration of PWM
		GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9|GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		GPIO_Init(GPIOA, &GPIO_InitStructure);

		// Pin configuration of PWM
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

			GPIO_Init(GPIOE, &GPIO_InitStructure);



		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_10);//Right front
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_2);



		TIM_TimeBaseStructure.TIM_Period = 4800-1;
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 4799;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

		TIM_OC3Init(TIM2, &TIM_OCInitStructure);
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);
		TIM_OC4Init(TIM1, &TIM_OCInitStructure);

		//enable the PWM output
		TIM_CtrlPWMOutputs(TIM2, ENABLE);
		TIM_Cmd(TIM2, ENABLE);


		TIM_SetCompare3(TIM2, 0);
		TIM_SetCompare2(TIM2, 0);

		TIM_CtrlPWMOutputs(TIM1, ENABLE);
		TIM_Cmd(TIM1, ENABLE);

		TIM_SetCompare4(TIM1, 0);





////////////////////////////////////////////////////////////////

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
  ADC1->SMPR1 |= ADC_SMPR1_SMP7_1 | ADC_SMPR1_SMP7_0; // = 0x03 => sampling time 7.5 ADC clock cycles
  ADC1->CR |= ADC_CR_ADEN; // Enable ADC1
  while(!ADC1->ISR & ADC_ISR_ADRD); // wait for ADRDY

  ADC1->CR |= ADC_CR_ADSTART; // Start ADC1 Software Conversion
	UART_Init();
 while (1)
  {
  while(!(ADC1->ISR & ADC_ISR_EOC)); // Test EOC flag
  ADC1ConvertedValue = ADC1->DR; // Get ADC1 converted data
  ADC1ConvertedVoltage = (ADC1ConvertedValue *3300)/4096; // Compute the voltage
  if( ADC1ConvertedValue >0)
  {
	  TIM_SetCompare4(TIM1,ADC1ConvertedValue);// Compute the voltage
	 if(ADC1ConvertedValue<=60)
	  USART_SendData(UART4,'s');
	 //else
	//	 USART_SendData(UART4,'p');
	  //uarttransmit('j');
  //else
	//  TIM_SetCompare4(TIM1,2500);
  }

	 // uarttransmit('n');
  }
 }

