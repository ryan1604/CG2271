#include "basic.h"
#include "motors.h"

#define LEFT_FRONT_FORWARD 0b10000000
#define LEFT_FRONT_REVERSE 0b01000000
#define LEFT_BACK_FORWARD 0b00100000
#define LEFT_BACK_REVERSE 0b00010000
#define RIGHT_BACK_FORWARD 0b00001000
#define RIGHT_BACK_REVERSE 0b00000100
#define RIGHT_FRONT_FORWARD 0b00000010
#define RIGHT_FRONT_REVERSE 0b00000001
#define MOTOR_FORWARD 0b10101010
#define MOTOR_REVERSE 0b01010101
#define MOTOR_STOP 0b11111111

void stop () {
	PTC->PCOR = MOTOR_STOP;
}

void forward () {
	PTC->PSOR = MOTOR_FORWARD;
}

void reverse () {
	PTC->PSOR = MOTOR_REVERSE;
}

void turnLeft () {
	PTC->PSOR = RIGHT_FRONT_FORWARD;
	PTC->PSOR = RIGHT_BACK_FORWARD;
	PTC->PSOR = LEFT_FRONT_REVERSE;
	PTC->PSOR = LEFT_BACK_REVERSE;
}

void turnRight () {
	PTC->PSOR = RIGHT_FRONT_REVERSE;
	PTC->PSOR = RIGHT_BACK_REVERSE;
	PTC->PSOR = LEFT_FRONT_FORWARD;
	PTC->PSOR = LEFT_BACK_FORWARD;
}

void swerveRight () {
	PTC->PSOR = LEFT_FRONT_FORWARD;
	PTC->PSOR = LEFT_BACK_FORWARD;
	PTC->PSOR = RIGHT_BACK_REVERSE;
}

void swerveLeft () {
	PTC->PSOR = RIGHT_FRONT_FORWARD;
	PTC->PSOR = RIGHT_BACK_FORWARD;
	PTC->PSOR = LEFT_BACK_REVERSE;
}
