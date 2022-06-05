
#include "tm4c123gh6pm.h"

void Init_UART(void );					//Initializing UART
char UART0_Receiver(void);			//Function to receive from UART0
void delay_MilliSec(int n);   	//Delay function 
void printstring(char *str);		//Function that sends string to UART0
void UART0_Send(uint8_t data);	//Function that sends character to UART0