
#include "port_init.h""

void init_portF(void)
{
	SYSCTL_RCGCGPIO_R = 0x20U;
	while(SYSCTL_PRGPIO_R & 0x20U == 0x00){}
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x011U;
	GPIO_PORTF_PUR_R = 0x011U;
  GPIO_PORTF_DIR_R = 0x0EU;
  GPIO_PORTF_DEN_R = 0x01FU;
}

void init_PE3_and_ADC0(void)
{
		/* enable clocks */
    SYSCTL_RCGCGPIO_R |= 0x10;      /* enable clock to GPIO_PORTE */
    SYSCTL_RCGCADC_R |= 1;          /* enable clock to ADC0 */
 
    /* initialize PE3 for AIN0 input */
    GPIO_PORTE_AFSEL_R |= 8;        /* enable alternate function */
    GPIO_PORTE_DEN_R &= ~8;         /* disable digital function */
    GPIO_PORTE_AMSEL_R |= 8;        /* enable analog function */
 
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */
    ADC0_SSMUX3_R = 0;              /* get input from channel 0 */
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 */
}