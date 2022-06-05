#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define IN 0
#define OUT 1

#define OPEN_DRAIN 1
#define NOT_OPEN_DRAIN 0

#define PULL_UP 1
#define PULL_DOWN 0

#include "types.h"

void DIO_Init(int8 port, int8 pin, int8 dir, int8 pull_status,  int8 open_drain_status);
void DIO_WritePin(int8 port, int8 pin,int8 bitval);
int8 DIO_ReadPin(int8 port, int8 pin);
void DIO_WritePort(int8 port,int32 bitval);
int32 DIO_ReadPort(int8 port);
void Toggle(int8 color);