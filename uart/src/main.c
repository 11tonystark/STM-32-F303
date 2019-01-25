
#include "stm32f30x.h"
#include "stm32f3_discovery.h"
			
void UART4_Init(uint32_t speed);
int main(void)
{
	UART4_Init(9600);
	//USART_SendData(UART4,'a');

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	// Initialization of GPIO PORTE PIN 13
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_13);
	for(;;)
	{
		if(USART_ReceiveData(UART4)=='a')
			GPIO_ResetBits(GPIOE,GPIO_Pin_13);
		else GPIO_SetBits(GPIOE,GPIO_Pin_13);
	}
}
void UART4_Init(uint32_t speed)
{

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* USARTx configured as follow:
				- BaudRate = speed parameter above
				- Word Length = 8 Bits
				- One Stop Bit
				- No parity
				- Hardware flow control disabled (RTS and CTS signals)
				- Receive and transmit enabled
	*/

	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	/* Enable USART clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	/* USART configuration */
	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);

	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure USART Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Connect PXx to USARTx_Tx */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_5);

	/* Connect PXx to USARTx_Rx */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_5);

	/* Enable USART */
	USART_Cmd(UART4, ENABLE);
}
