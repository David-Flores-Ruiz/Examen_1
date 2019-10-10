/*
 * @file:		Examen_1.c
 * @company:	ITESO
 * @Engineer:	D.F.R.
 */

#include <stdio.h>
#include "MK64F12.h"

#include "GPIO.h"
#include "NVIC.h"
#include "PIT.h"
#include "RGB.h"
#include "bits.h"

// #define DEBUG_ON

//#ifndef DEBUG_ON
//		printf("RED LED ON\n");	 // printf solamente para debuggear (con el primer #define).
//#endif



int main(void) {
	RGB_init();
	SW_init();
	PIT_init();

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	//NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_10);	// sw2
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_10);	// sw3
	NVIC_global_enable_interrupts;

	uint8_t state_sw2 = 0;
	uint8_t state_sw3 = 0;

	while (1) {





	}
	return 0;

}
