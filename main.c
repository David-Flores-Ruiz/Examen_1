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

#define SYSTEM_CLOCK (21000000U)
#define Delay_3s 	3		 /** Ventana de tiempo para checar SW2 */
#define Delay_5s	5		 /**     Intervalo para checar SW3	   */

typedef enum {
	Apagado,	Arranque,
	Azul,
	Verde,
	Rojo,
	Amarillo,
	Morado,
	Naranja,
} State_t;



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

	uint8_t state_sw2 = FALSE;
	uint8_t state_sw3 = FALSE;

	uint8_t status_PIT_0 = FALSE;
	uint8_t status_PIT_1 = FALSE;

	State_t current_state = Apagado;			// Estado inicial del sistema



	while (1) {

		PIT_delay(PIT_0, SYSTEM_CLOCK, Delay_3s);
		PIT_delay(PIT_1, SYSTEM_CLOCK, Delay_5s);

		state_sw2 = GPIO_get_irq_status(GPIO_C);	// Se lee si se presiono SW2
		state_sw3 = GPIO_get_irq_status(GPIO_A);	// Se lee si se presiono SW2

		status_PIT_0 = PIT_get_irq_flag_status(PIT_0);
		status_PIT_1 = PIT_get_irq_flag_status(PIT_1);

		if (state_sw2==TRUE & status_PIT_0) {
			encender_LED(RED_ON);
			encender_LED(GREEN_ON);
			encender_LED(BLUE_ON);

			current_state = Azul;
		}

		switch (current_state) {
		case Apagado:


			if (state_sw2 ) {

				printf("\nCLAVE_MAESTRA correcta!");
				GPIO_set_pin(GPIO_B, bit_18); /** Power On: GREEN LED */
				current_state = Azul;
			}
			break; // end case waitCLAVE_MAESTRA

		case Arranque:

			break;

		case Azul:

			break;

		case Verde:

			break;

		case Rojo:

			break;

		case Amarillo:

			break;

		case Morado:

			break;

		case Naranja:

			break;

		default:
			break;
		} //end switch(current state)




		state_sw3 = GPIO_get_irq_status(GPIO_A);	// Se lee si se presiono SW3



	}
	return 0;

}
