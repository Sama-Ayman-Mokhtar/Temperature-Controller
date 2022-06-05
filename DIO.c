#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "DIO.h"

void DIO_Init(int8 port, int8 pin, int8 dir, int8 pull_status,  int8 open_drain_status)
{
  Set_bit(SYSCTL_RCGCGPIO_R,port)
  while(Get_Bit(SYSCTL_PRGPIO_R,port) == 0)
  {
    
  }
  
  switch(port)
  {
  case PORTA:
    GPIO_PORTA_LOCK_R=0x4C4F434B;
    Set_bit(GPIO_PORTA_CR_R,pin)
    if (dir)
      Set_bit(GPIO_PORTA_DIR_R,pin)
    else
      Clear_bit(GPIO_PORTA_DIR_R,pin)
        
    if (open_drain_status)
      Set_bit(GPIO_PORTA_ODR_R,pin)
     else
      Clear_bit(GPIO_PORTA_ODR_R,pin)
        
    if (pull_status)
       Set_bit(GPIO_PORTA_PUR_R,1)
     //else
      // Set_bit(GPIO_PORTA_PDR_R,1)  
      
    Set_bit(GPIO_PORTA_DEN_R,pin)
    break;
    
  case PORTB:
    GPIO_PORTB_LOCK_R=0x4C4F434B;
    Set_bit(GPIO_PORTB_CR_R,pin)
    if (dir)
      Set_bit(GPIO_PORTB_DIR_R,pin)
    else
      Clear_bit(GPIO_PORTB_DIR_R,pin)
        
     if (open_drain_status)
      Set_bit(GPIO_PORTB_ODR_R,pin)
     else
      Clear_bit(GPIO_PORTB_ODR_R,pin)
        
    if (pull_status)
       Set_bit(GPIO_PORTB_PUR_R,1)
     //else
     //  Set_bit(GPIO_PORTB_PDR_R,1)
   
    Set_bit(GPIO_PORTB_DEN_R,pin)
    break;
      
  case PORTC:
    GPIO_PORTC_LOCK_R=0x4C4F434B;
    Set_bit(GPIO_PORTC_CR_R,pin)
      
    if (dir)
      Set_bit(GPIO_PORTC_DIR_R,pin)
    else
      Clear_bit(GPIO_PORTC_DIR_R,pin)
        
     if (open_drain_status)
      Set_bit(GPIO_PORTC_ODR_R,pin)
     else
      Clear_bit(GPIO_PORTC_ODR_R,pin)
        
    if (pull_status)
       Set_bit(GPIO_PORTC_PUR_R,1)
     //else
      // Set_bit(GPIO_PORTC_PDR_R,1)
    
    Set_bit(GPIO_PORTC_DEN_R,pin)
    break;
    
   case PORTD:
    GPIO_PORTD_LOCK_R=0x4C4F434B;
    Set_bit(GPIO_PORTD_CR_R,pin)
    if (dir)
      Set_bit(GPIO_PORTD_DIR_R,pin)
    else
      Clear_bit(GPIO_PORTD_DIR_R,pin)
        
     if (open_drain_status)
      Set_bit(GPIO_PORTD_ODR_R,pin)
     else
      Clear_bit(GPIO_PORTD_ODR_R,pin)
        
    if (pull_status)
       Set_bit(GPIO_PORTD_PUR_R,1)
    // else
     //  Set_bit(GPIO_PORTD_PDR_R,1)
        
    Set_bit(GPIO_PORTD_DEN_R,pin)
    break;
    
   case PORTE:
    GPIO_PORTE_LOCK_R=0x4C4F434B;
    Set_bit(GPIO_PORTE_CR_R,pin)
    if (dir)
      Set_bit(GPIO_PORTE_DIR_R,pin)
    else
      Clear_bit(GPIO_PORTE_DIR_R,pin)
        
     if (open_drain_status)
      Set_bit(GPIO_PORTE_ODR_R,pin)
     else
      Clear_bit(GPIO_PORTE_ODR_R,pin)
        
    if (pull_status)
       Set_bit(GPIO_PORTE_PUR_R,1)
    // else
      // Set_bit(GPIO_PORTE_PDR_R,1)
         
    Set_bit(GPIO_PORTE_DEN_R,pin)
    break;
    
   case PORTF:
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    Set_bit(GPIO_PORTF_CR_R,pin)
    if (dir)
      Set_bit(GPIO_PORTF_DIR_R,pin)
    else
      Clear_bit(GPIO_PORTF_DIR_R,pin)
        
     if (open_drain_status)
      Set_bit(GPIO_PORTF_ODR_R,pin)
     else
      Clear_bit(GPIO_PORTF_ODR_R,pin)
        
    if (pull_status)
       Set_bit(GPIO_PORTF_PUR_R,1)
     else
       Set_bit(GPIO_PORTF_PDR_R,1)
    
    Set_bit(GPIO_PORTF_DEN_R,pin)
    break;
  }
}

void DIO_WritePin(int8 port, int8 pin, int8 bitVal)
{
   switch(port)
  {
  case PORTA:
    if (bitVal)
    {
       Set_bit(GPIO_PORTA_DATA_R,pin)
    }
    else
    {
      Clear_bit(GPIO_PORTA_DATA_R,pin)
    }
    break;
    
  case PORTB:
   if (bitVal)
    {
       Set_bit(GPIO_PORTB_DATA_R,pin)
    }
    else
    {
      Clear_bit(GPIO_PORTB_DATA_R,pin)
    }
    break;
    
  case PORTC:
     if (bitVal)
    {
       Set_bit(GPIO_PORTC_DATA_R,pin)
    }
    else
    {
      Clear_bit(GPIO_PORTC_DATA_R,pin)
    }
    break;
    
   case PORTD:
     if (bitVal)
    {
       Set_bit(GPIO_PORTD_DATA_R,pin)
    }
    else
    {
      Clear_bit(GPIO_PORTD_DATA_R,pin)
    }
    break;
    
   case PORTE:
     if (bitVal)
    {
       Set_bit(GPIO_PORTE_DATA_R,pin)
    }
    else
    {
      Clear_bit(GPIO_PORTE_DATA_R,pin)
    }
    break;
    
   case PORTF:
     if (bitVal)
    {
       Set_bit(GPIO_PORTF_DATA_R,pin)
    }
    else
    {
      Clear_bit(GPIO_PORTF_DATA_R,pin)
    }
    break;
  }
}

//ToBeTested
void DIO_WritePort(int8 port,int32 bitval)
{
   switch(port)
  {
  case PORTA:
    GPIO_PORTA_DATA_R = bitval;
    break;
   
  case PORTB:
    GPIO_PORTB_DATA_R = bitval;
    break;
    
  case PORTC:
    GPIO_PORTC_DATA_R = bitval;
    break;
    
   case PORTD:
    GPIO_PORTD_DATA_R = bitval;
    break;
    
   case PORTE:
    GPIO_PORTE_DATA_R = bitval;
    break;
    
   case PORTF:
    GPIO_PORTF_DATA_R = bitval;
    break;
  }
}


int8 DIO_ReadPin(int8 port, int8 pin)
{
   switch(port)
  {
  case PORTA:
   return Get_Bit(GPIO_PORTA_DATA_R,pin); 
   break;
   
  case PORTB:
   return Get_Bit(GPIO_PORTB_DATA_R,pin);
   break;
   
  case PORTC:
   return Get_Bit(GPIO_PORTC_DATA_R,pin);
   break;
   
  case PORTD:
   return Get_Bit(GPIO_PORTD_DATA_R,pin);
   break;
   
  case PORTE:
   return Get_Bit(GPIO_PORTE_DATA_R,pin);
   break;
   
  case PORTF:
   return  Get_Bit(GPIO_PORTF_DATA_R,pin);
   break;
   
  default:
    return -1;
  }
}


//ToBeTested
//ToBeTested
int32 DIO_ReadPort(int8 port)
{
   switch(port)
  {
  case PORTA:
    return GPIO_PORTA_DATA_R;
    break;
   
  case PORTB:
    return GPIO_PORTB_DATA_R;
    break;
    
  case PORTC:
    return GPIO_PORTC_DATA_R;
    break;
    
   case PORTD:
    return GPIO_PORTD_DATA_R;
    break;
    
   case PORTE:
    return GPIO_PORTE_DATA_R;
    break;
    
   case PORTF:
    return GPIO_PORTF_DATA_R;
    break;
    
   default:
    return -1;
  }
}


void Toggle(int8 color)
{
    for(int count=0;count<3;count++)
     {
     DIO_WritePin(PORTF,color,1);
     int volatile counter=0;
     while(counter<1000000)
     {
       ++counter;
     }
     
     DIO_WritePin(PORTF,color,0);
     counter=0;
     while(counter<1000000)
     {
       ++counter;
     }
    }
}