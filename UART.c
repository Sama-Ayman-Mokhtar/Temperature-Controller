
#include "UART.h"

void Init_UART(void ){

	SYSCTL_RCGCGPIO_R |= 0x01U;		/* enable clock to PORTA for PA0/PA1 Tx/Rx */
	SYSCTL_RCGCUART_R |= 0x01U; 	/* enable clock to UART0 */				
	while(SYSCTL_PRGPIO_R & 0x01U == 0x00){}										
	UART0_CTL_R &= ~0x001;			/* UART0 module disbable */														
	UART0_IBRD_R = 104;					/* for 9600 baud rate, integer = 104 */
	UART0_FBRD_R = 11;					/* for 9600 baud rate, fractional = 11*/
	UART0_CC_R = 0;							/*select system clock*/
	UART0_LCRH_R = 0x060;				/* data lenght 8-bit, not parity bit, no FIFO */
	UART0_CTL_R = 0x0301;				/* Enable UART0 module, Rx and Tx */
	GPIO_PORTA_AFSEL_R |= 0x03; /* Use PA0, PA1 alternate function */																	 
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0XFFFFFF00) + 0X011; /* configure PA0 and PA1 for UART */
	GPIO_PORTA_DEN_R |= 0x03; 		/* set PA0 and PA1 as digital */																
	GPIO_PORTA_AMSEL_R &= ~0x03; 	/* Turn off analg function*/																
}
void UART0_Send(uint8_t data)  
{
    while((	UART0_FR_R& 0x20) != 0); /* wait until Tx buffer not full */
    UART0_DR_R = data;      					/* before giving it another byte */           
}
char UART0_Receiver(void)  
{
    char data;
	  while((UART0_FR_R & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = UART0_DR_R ;  								/* before giving it another byte */
    return (unsigned char) data; 
}
void printstring(char *str)
{
	//looping over a string and sending character by character to UART
  while(*str)
	{
		UART0_Send(*(str++));
	}
}
void delay_MilliSec(int n)
{
	for(int i = 0 ; i < n; i++)
	{
		for(int j = 0 ; j < 3180; j++);
	}
}