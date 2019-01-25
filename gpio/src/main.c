#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>

int main(void)
{
	volatile unsigned int i=0;
	//Enable clock for GPIOE
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

	//SET GPIO PIN 13 as output
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	// Initialization of GPIO PORTE PIN 13
	GPIO_Init(GPIOE,&GPIO_InitStruct);

    while(1)
    {
    	GPIO_SetBits(GPIOE,GPIO_Pin_13); //set pin 13 high
    	for ( i = 0; i < 1000000; ++i) ; //delay
    	//GPIO_ResetBits(GPIOE,GPIO_Pin_13); //set pin 13 low
    	//for ( i = 0; i < 1000000; ++i) ; //delay
    }
}
