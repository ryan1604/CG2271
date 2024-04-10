#include "basic.h"

volatile int isMoving = 0;
volatile int isComplete = 0;

/* Delay function */
static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}
