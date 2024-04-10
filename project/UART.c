#include "basic.h"
#include "UART.h"

#define UART2_INT_PRIO 128

/* Init UART2*/
void initUART2 (uint32_t baud_rate) {
	uint32_t divisor, bus_clock;
	
	// Enable Clock for Uart2 and PortD
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	//PORTE->PCR[UART_TX_PORTE22] &= ~PORT_PCR_MUX_MASK;
	//PORTE->PCR[UART_TX_PORTE22] |= PORT_PCR_MUX(4);
	
	// Configure MUX to enable UART2 on PortD Pin 2
	PORTD->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(3);
	
	UART2->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
	// Enable UART2 receive interrupts
	
	bus_clock = DEFAULT_SYSTEM_CLOCK / 2;
	divisor = bus_clock / (baud_rate * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);
	
	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	UART2->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;
	UART2->C2 |= UART_C2_RIE_MASK; // Set RIE to enable receive interrupts
	
	NVIC_SetPriority(UART2_IRQn, UART2_INT_PRIO);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
}
