

#include "stm32f30x.h"
#include "stm32f3_discovery.h"


void Delay(int time)
{
	volatile int i,j;

	time = time*1000; ///milli ko sec but input par depend karega
	for (i=0;i<time;i++)
		j++;
}

int uartreceive()
{
	int cnt=0;
	//Waiting for register to update
	while(!USART_GetFlagStatus(UART4, USART_FLAG_RXNE))
	{
		cnt++;
		if(cnt>2000)
			break;
	}
	return USART_ReceiveData(UART4);
}

void Stopthearm(void)
{

	GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 );
}


void gpioinit()
{

	//Enable clock for GPIOE
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);

		//SET GPIO PIN 10, 12, 13 as output pins
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

		// Initialization of GPIO PORT E Pin 10, 13 and Pin 12
		GPIO_Init(GPIOE,&GPIO_InitStruct);
		GPIO_ResetBits(GPIOE,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);

	//Enable clock for GPIOA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

	//SET GPIO PIN 0,1,2,3,4,5,6, as output pins
	//GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;


	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);

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
	USART_InitStructure.USART_BaudRate = 19200;
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


void DCServomotor2F(void)
{
	//clockwise
	GPIO_SetBits(GPIOE,GPIO_Pin_0);
	    		GPIO_SetBits(GPIOE,GPIO_Pin_1);
	    		Delay(5);

	    		 GPIO_ResetBits(GPIOE,GPIO_Pin_0);
	         	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	         	Delay(5);
	//PIN1 DIRECTION,PIN0 PULSE
}


void DCServomotor2B(void)
{
	//anti clockwise
	GPIO_ResetBits(GPIOE,GPIO_Pin_0);
	    		GPIO_SetBits(GPIOE,GPIO_Pin_1);
	    		Delay(5);

	    		 GPIO_SetBits(GPIOE,GPIO_Pin_0);
	         	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	         	Delay(5);
	//PIN1 DIRECTION,PIN0 PULSE
}
void DCServogripperF(void)
{
	//clockwise
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	    		GPIO_SetBits(GPIOE,GPIO_Pin_2);
	    		Delay(5);

	    		 GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	         	GPIO_ResetBits(GPIOE,GPIO_Pin_2);
	         	Delay(5);
	//PIN2 DIRECTION,PIN3 PULSE
}


void DCServogripperB(void)
{
	//anti clockwise
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	    		GPIO_SetBits(GPIOE,GPIO_Pin_2);
	    		Delay(5);

	    		 GPIO_SetBits(GPIOE,GPIO_Pin_3);
	         	GPIO_ResetBits(GPIOE,GPIO_Pin_2);
	         	Delay(5);
	//PIN2 DIRECTION,PIN3 PULSE
}

void DCServostop(void)
{
	//stop

         	GPIO_ResetBits(GPIOE,GPIO_Pin_0);
         	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
         	GPIO_ResetBits(GPIOE,GPIO_Pin_2);
        	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
         	Delay(1);
      		 GPIO_ResetBits(GPIOE,GPIO_Pin_0);
           	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
            GPIO_ResetBits(GPIOE,GPIO_Pin_2);
           	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
           	Delay(1);

}


void armcode( char motor)
{
	if(motor=='A')
		{
			//dc servolink2 forward
		 DCServomotor2F();
		}
	else if(motor=='B')
		{
			//dc servolink2 backward
		 DCServomotor2B();
		}

	else if(motor=='C')
		{
		DCServogripperF();
			//dc servo gripperforward

		}
	else if(motor=='D')
		{
		//dc servo gripper back
		 DCServogripperB();
		}
	else if(motor=='E')
		{ //linear act, f
			GPIO_SetBits(GPIOA,GPIO_Pin_4);//dirc
			GPIO_SetBits(GPIOA,GPIO_Pin_5);//gpio
		}
	else if(motor=='F')
		{//linear act.  b
			GPIO_SetBits(GPIOA,GPIO_Pin_4);//dirc
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);//gpio
		}
	else if(motor=='G')
		{//pitch f
			GPIO_SetBits(GPIOA,GPIO_Pin_6);//direc
			GPIO_SetBits(GPIOA,GPIO_Pin_7);//gpio
		}
	else if(motor=='H')
		{//pitch  b
			GPIO_SetBits(GPIOA,GPIO_Pin_6);//dirc
			GPIO_ResetBits(GPIOA,GPIO_Pin_7);//gpio
		}
	else if(motor=='I')
		{//roll  f
			GPIO_SetBits(GPIOA,GPIO_Pin_8);//direc
			GPIO_SetBits(GPIOA,GPIO_Pin_9);//gpio
		}
	else if(motor=='J')
		{//roll  b
			GPIO_SetBits(GPIOA,GPIO_Pin_8);//direc
			GPIO_ResetBits(GPIOA,GPIO_Pin_9);//gpio
		}
	else if(motor=='K')
	{
		Stopthearm();
		//GPIO_SetBits(GPIOE,GPIO_Pin_9);

		}

	else
			{
		DCServostop();
			}
}


int main(void)
{
	int cnt=0;
	char dp;
//int d=0;
char d;
char motor;
	gpioinit();
	UART_Init();
	// Stopthearm();
	while(1)
	{
		d=USART_ReceiveData(UART4);


				// dp=d;
			     if(d=='n')
				{
                    motor= uartreceive();

			    	 GPIO_SetBits(GPIOE,GPIO_Pin_8);
			    	 if(motor=='E')
			    	 {
			    	 		 //linear act, f
			    	 			GPIO_SetBits(GPIOA,GPIO_Pin_4);//dirc
			    	 			GPIO_SetBits(GPIOA,GPIO_Pin_5);//gpio
			    	 }

			    	 	else if(motor=='F')
			    	 		{//linear act.  b
			    	 			GPIO_SetBits(GPIOA,GPIO_Pin_4);//dirc
			    	 			GPIO_ResetBits(GPIOA,GPIO_Pin_5);//gpio
					//continue;
				}

			    	 	else if(motor=='G')
			    	 			{//pitch f
			    	 				GPIO_SetBits(GPIOA,GPIO_Pin_6);//direc
			    	 				GPIO_SetBits(GPIOA,GPIO_Pin_7);//gpio
			    	 			}
			    	 		else if(motor=='H')
			    	 			{//pitch  b
			    	 				GPIO_SetBits(GPIOA,GPIO_Pin_6);//dirc
			    	 				GPIO_ResetBits(GPIOA,GPIO_Pin_7);//gpio
			    	 			}
			    	 		else if(motor=='I')
			    	 			{//roll  f
			    	 			Stopthearm();
			    	 			}
			    	 		else if(motor=='J')
			    	 			{//roll  b
			    	 			Stopthearm();
			    	 			}

			    	 }
				else
					{
					 //Stopthearm();
					 GPIO_ResetBits(GPIOE,GPIO_Pin_8);
				//	 DCServostop();
					// continue;

					}

				}
		/*
		 d=USART_ReceiveData(UART4);
		// dp=d;
	     if(d=='a')
		{
	    	// Stopthearm();
	    	// dp=d;
			GPIO_SetBits(GPIOE,GPIO_Pin_8);
	//
			armcode(uartreceive());

			continue;
		}

		else
			{
			 Stopthearm();
			 GPIO_ResetBits(GPIOE,GPIO_Pin_8);
		//	void DCServostop();
				continue;

			}
	  /*   if(dp==d)
	     		{
	     			cnt++;
	     			if(cnt>1000)
	     			{
	     				Stopthearm();
	     				continue;
	     			}
	     		}
	     		else
	     		{
	     			cnt=0;
	     		}

	}



	*/
	}


