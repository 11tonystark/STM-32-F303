#include <stm32f30x.h>
//#include <stm32f30x_rcc.h>
//#include <stm32f30x_gpio.h>
#include <time.h>

//void delay(int time);


void Delay(int time)
{
	volatile int i,j;

	time = time*1000;
	for (i=0;i<time;i++)
		j++;
}


int main(void)
{
	unsigned int input_val;
	//volatile unsigned int i=0;

	//Enable clock for both GPIOE and GPIOA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	//configuration for led connected to PE13
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//configuration for user button connected to PA0
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
//PIN12 DIRECTION,PIN13 PULSE
    while(1)
    {
    	input_val = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
    	if (input_val ==1)
    		{
//clockwise
/*
    		GPIO_SetBits(GPIOA,GPIO_Pin_9);
    		GPIO_SetBits(GPIOA,GPIO_Pin_8);
    		Delay(7);
    		// Delay(100);
    		 GPIO_ResetBits(GPIOA,GPIO_Pin_9);
         	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
         	Delay(7);
             //Delay(10);
*/

         	//stop
/*
         	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
         	GPIO_ResetBits(GPIOE,GPIO_Pin_12);
         	Delay(1);
      		 GPIO_ResetBits(GPIOE,GPIO_Pin_13);
           	GPIO_ResetBits(GPIOE,GPIO_Pin_12);
           	Delay(1);

*/
        	//anticlock

      	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
                 	GPIO_SetBits(GPIOA,GPIO_Pin_8);
                 	Delay(7);
              		 GPIO_SetBits(GPIOA,GPIO_Pin_9);
                   	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
                   	Delay(7);


    		}
    	 else if (input_val==0)
    	 {
    		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
         	GPIO_ResetBits(GPIOE,GPIO_Pin_12);
         	Delay(1);
      		 GPIO_ResetBits(GPIOE,GPIO_Pin_13);
           	GPIO_ResetBits(GPIOE,GPIO_Pin_12);
           	Delay(1);
    	 }
    	}
}


