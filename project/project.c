/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "basic.h"
#include "GPIO.h"
#include "UART.h"
#include "audio.h"
#include "motors.h"
#include "led.h"

#define BAUD_RATE 9600

typedef struct {
	uint8_t cmd;
} dataPkt;

osMessageQueueId_t motorCtlMsg, robotCtlMsg;

/* Interrupt to receive data from ESP32 */
void UART2_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART2_IRQn);
	dataPkt rxData;
	if (UART2->S1 & UART_S1_RDRF_MASK) { // Check if receive data register is full
    rxData.cmd = UART2->D; // Read the received data (also clears RDRF flag)
		osMessageQueuePut(robotCtlMsg, &rxData, NULL, 0); // Send data to main robot control to execute command
  }
}

/* Thread to control robot movement */
void motorControl (void *argument) {
	dataPkt rxData;
	osStatus_t status;
	for (;;) {
		status = osMessageQueueGet(motorCtlMsg, &rxData, NULL, osWaitForever);
		if (status == osOK) {
			switch (rxData.cmd) {
			case 0x00:
				stop();
				break;
			case 0x01:
				forward();
				break;
			case 0x02:
				reverse();
				break;	
			case 0x08:
				turnLeft();
				break;
			case 0x09:
				swerveLeft();
				break;
			case 0x05:
				swerveRight();
				break;
			case 0x04:
				turnRight();
				break;
			default:
				stop();
				break;
			}
		}
	}
}

/* Test motor movement
void motor_forward (void *argumetn) {
	for (;;) {
		PTC->PSOR = 0b10101010;
	}
}*/

/* Thread to control LED
void led_thread (void *argument) {
	PTB->PSOR = 0xF0F;
	PTE->PSOR = 0b111111 | (0b1111 << 20) | (0b11 << 29);
	for (;;) {}
}*/

/* Thread to control front LEDs */
int front_orderE[] = {21, 20, 5, 4, 3, 2}; // pins for
int front_orderB[] = {11, 8, 9, 10};       // front led
void front_led_thread (void *argument) {
	int lastEIdx = 0;
	int lastBIdx = 0;

	while (1) {
		if (isMoving) {
			offFrontLEDs();
			// On LEDs one at a time when robot is moving
			while (lastEIdx < 6) {
				PTE->PSOR = 1 << front_orderE[lastEIdx];
				osDelay(500);
				PTE->PCOR = 1 << front_orderE[lastEIdx];
				lastEIdx++;
				if (!isMoving) {
					break;
				}
			}
			while (lastBIdx < 4) {
				if (!isMoving) {
					break;
				}
				PTB->PSOR = 1 << front_orderB[lastBIdx];
				osDelay(500);
				PTB->PCOR = 1 << front_orderB[lastBIdx];
				lastBIdx++;
			}
			if (lastEIdx >= 6 && lastBIdx >= 4) {
				lastEIdx = 0;
				lastBIdx = 0;
			}
		} else {
			// Turn all LEDs on when robot is stationary
			onFrontLEDs();
		}
	}
}

/* Thread to control back LEDs */
void back_led_thread (void *argument) {
	while (1) {
		if (isMoving) {
			// All LEDs blink at 1hz
			onBackLEDs();
			osDelay(500);
			offBackLEDs();
			osDelay(500);
		} else {
			// All LEDs blink at 2hz
			onBackLEDs();
			osDelay(250);	
			offBackLEDs();
			osDelay(250);
		}
	}
}

/* Thread to control buzzer */
void buzzer (void *arguement) {
	while (1) {
		if (!isComplete) {
			playSong();
		} else {
			playCelebrationSong();
		}
	}
}

/* Thread to handle commands received by UART2 Interrupt */
void mainRobotBrainControl (void *argument) {
	dataPkt myData;
	osStatus_t status;
	for (;;) {
		osMessageQueueGet(robotCtlMsg, &myData, NULL, osWaitForever);
		if (status == osOK) {
			if (myData.cmd == 0x00) {
				isMoving = 0;
			} else {
				isMoving = 1;
			}
			if (myData.cmd == 0x11) {
				isComplete = 1;
			}
			osMessageQueuePut(motorCtlMsg, &myData, NULL, 0);
		}
	}
}

int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  initGPIO();
	initPWM();
	initUART2(BAUD_RATE);
	
  osKernelInitialize();                 // Initialize CMSIS-RTOS
	robotCtlMsg = osMessageQueueNew(1, sizeof(dataPkt), NULL);
	motorCtlMsg = osMessageQueueNew(1, sizeof(dataPkt), NULL);
	
	osThreadNew(motorControl, NULL, NULL);
	osThreadNew(mainRobotBrainControl, NULL, NULL);
	osThreadNew(front_led_thread, NULL, NULL);
	osThreadNew(back_led_thread, NULL, NULL);
	//osThreadNew(motor_forward, NULL, NULL);
	osThreadNew(buzzer, NULL, NULL);
	
  osKernelStart();                      // Start thread execution
  for (;;) {
	}
}
