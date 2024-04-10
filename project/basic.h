#ifndef BASIC_H
#define BASIC_H

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#define MASK(x) 	(1 << (x))

extern volatile int isMoving;
extern volatile int isComplete;

static void delay(volatile uint32_t nof);

#endif
