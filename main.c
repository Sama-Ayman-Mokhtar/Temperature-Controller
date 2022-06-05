#include "FreeRTOS.h"
#include "queue.h"
#include "DIO.h"

#include "LCD.h"
#include "UART.h"
#include "port_init.h"


void LCD_TASK(void *);
void LED_TASK(void *);
void UART_TASK(void *);
void Controller_Task(void);

//stores the messages to be displayed on LCD (each composed of a measured value and a setpoint)
xQueueHandle xQueue_LCD;
//stores the state(on or off) of the red led (replacement of the buzzer) 
xQueueHandle xQueue_LED;
//stores the setpoint passed from the keyboard as input 
xQueueHandle xQueue_UART;

typedef struct Message{
		int setPoint;
		int measuredPoint;
}Message;

void UART_TASK(void *)
{
	unsigned input;
	int setPoint;
	
	for( ;; )
	{	
		//displays on putty the message below
		printstring("\n\r\n\rEnter Temperature Setpoint (Degrees): "); 
		
		input = 0;
		setPoint = 0;
		while(1)
		{
			//recieves input value form keyboard
			input = UART0_Receiver();
			//displays that input on putty
			UART0_Send(input); 
			
			//loops so long as enter is not yet recieved
			if(input == '\r')
			{
				break;
			}
			
			//maps characters to numbers (digit by digit)
			input = input - '0';
			setPoint = 10*setPoint + input;	
		}
		//sends the full number into the UART queue
		xQueueSendToBack( xQueue_UART, &setPoint, pdMS_TO_TICKS(10));
		//displays on putty the message below
		printstring("\n\rTemperature Setpoint Changed... ");
		
	}
}

void LCD_TASK(void *)
{
	 int setPoint;
	 int measured;
	 Message msg;
	 char text_measured[5];
	 char text_setPoint[5];

	for( ;; )
	{	
			//clears the display
			LCD4bits_Cmd(0x01);	
			//recieves the message object (composed of setpoint and mesaured value)
		  xQueueReceive( xQueue_LCD, &msg, 0);
			setPoint = msg.setPoint;
		  measured = msg.measuredPoint;
			
		  //forces the cursor to beginning of 1st line and displays measured value on LCD
		  LCD4bits_Cmd(0x80);               
			LCD_WriteString("Measured: ");
			sprintf(text_measured, "%d", measured);
		  LCD_WriteString(&text_measured);
			
			//forces the cursor to beginning of 2nd line and displays setpoint on LCD
		  LCD4bits_Cmd(0xC0);               
			LCD_WriteString("Setpoint: ");
		  sprintf(text_setPoint, "%d", setPoint);		
		  LCD_WriteString(&text_setPoint);
			vTaskDelay(pdMS_TO_TICKS(300));
			
	}
}

void LED_TASK(void *)
{
	unsigned char led_state = 0;
	
	for(;;)
	{
		//recieves the state of the red led
		xQueueReceive( xQueue_LED, &led_state, 0);
		
		//if true, turns red led on else off
		if(led_state)
		{
			GPIO_PORTF_DATA_R = 0x02;
		}
		else
		{
			GPIO_PORTF_DATA_R = 0x00;
		}
	}
	
}

void Controller_Task(void)
{
	
	int setPoint = 30;
	int potentiometer_val;
	int alert = 80; 
	char text[5];
	
	char* on = 1;
	char* off = 0;
	
	Message msg;
	char text_setPoint[5];
	for(;;)
	{
				xQueueReceive( xQueue_UART, &setPoint, 0);
				sprintf(text_setPoint, "%d", setPoint/40);
		
				//starts a conversion sequence 3 
				ADC0_PSSI_R |= 8;
				//waits for conversion to complete
        while((ADC0_RIS_R & 0x08) == 0); 
				//reads analog voltage from potentiometer (divides by 40 to scale the range down)
				potentiometer_val = ADC0_SSFIFO3_R/40; 
				//clears completion flag
        ADC0_ISC_R = 8;              
				
				memset(text,0,sizeof(text));
				sprintf(text, "%d", potentiometer_val);
				
				//if measured value is less than setpoint turn the heater on (represented by a blue led)
				if(potentiometer_val < setPoint)
				{
								GPIO_PORTF_DATA_R = 0x04;
				}else
				{
								GPIO_PORTF_DATA_R = 0x00;

				}
				msg.setPoint = setPoint;
				msg.measuredPoint	= potentiometer_val;		
				xQueueSendToBack( xQueue_LCD, &msg, 0);
				
				//if the measured value is greater than the threshold set status of led as on and append to queue
				if(potentiometer_val > alert)
				{
					xQueueSendToBack( xQueue_LED, &on, 0);
				}
				else
				{
					xQueueSendToBack( xQueue_LED, &off, 0);
				}
	}
}

int main(void)
{
		Init_UART();											// Initailize UART
		init_portF();                     // Initialize portF
		LCD4bits_Init();									// Initializate LCD
	  init_PE3_and_ADC0();							// initialzed Port as Analog (potentiometer - sensor replacement) 
	  
		//queues of size 1
		xQueue_UART = xQueueCreate( 1, sizeof(int)); 
		xQueue_LCD = xQueueCreate( 1, 2 * sizeof(Message));
		xQueue_LED = xQueueCreate( 1, 1); 
		
	if( xQueue_UART != NULL )
		{
			//creating the four tasks
			xTaskCreate( UART_TASK, "UART_TASK", 240, NULL, 2, NULL );
			xTaskCreate( LED_TASK, "LED_TASK", 240, NULL, 2, NULL );
			xTaskCreate( LCD_TASK, "LCD_TASK", 240, NULL, 2, NULL );
			xTaskCreate( Controller_Task, "LED_TASK", 240, NULL, 2, NULL );
			
			//displays on putty the message below
			printstring("start \n");

			vTaskStartScheduler();
		}
}

	