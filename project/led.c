#include "basic.h"
#include "led.h"

void offFrontLEDs () {
	PTE->PCOR = (0b1111 << 2) | (0b11 << 20);
	PTB->PCOR = 0b1111 << 8;
}

void onFrontLEDs() {
	PTE->PSOR = (0b1111 << 2) | (0b11 << 20);
	PTB->PSOR = 0b1111 << 8;
}

void onBackLEDs () {
	PTB->PSOR = 0b1111;
	PTE->PSOR = 0b11 | (0b11 << 22) | (0b11 << 29);
}

void offBackLEDs () {
	PTB->PCOR = 0b1111;
	PTE->PCOR = 0b11 | (0b11 << 22) | (0b11 << 29);
}
