#include "basic.h"
#include "GPIO.h"

void initGPIO(void)
{
  // Enable Clock to PORTB, PORTC and PORTE
  SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTE_MASK);
	
	// Configure MUX settings to enable GPIO for Motors
	PORTC->PCR[0] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[0] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[1] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[1] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[2] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[2] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[3] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[3] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[4] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[4] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[5] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[5] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[6] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[6] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[7] &= ~PORT_PCR_MUX_MASK;
  PORTC->PCR[7] |= PORT_PCR_MUX(1);
	
	// Configure MUX settings to enable GPIO for LEDs
	PORTB->PCR[0] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[0] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[1] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[1] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[2] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[2] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[3] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[3] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[8] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[8] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[9] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[9] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[10] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[10] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[11] &= ~PORT_PCR_MUX_MASK;
  PORTB->PCR[11] |= PORT_PCR_MUX(1);
	
	int portEArr[] = {0, 1, 2, 3, 4, 5, 20, 21, 22, 23, 29, 30};
	for (int i = 0; i < 12; i++) {
		PORTE->PCR[portEArr[i]] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[portEArr[i]] |= PORT_PCR_MUX(1);
	}
	
  // Set Data Direction Registers for PortB, PortC and PortE
	PTB->PDDR |= 0xF0F;
	PTC->PDDR |= 0b11111111;
	PTE->PDDR |= 0b111111 | (0b1111 << 20) | (0b11 << 29);
}
