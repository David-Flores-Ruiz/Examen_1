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

#define Delay_3s 	3		 /** Ventana de tiempo para checar SW2 */

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

	uint8_t state_sw2 = 0;
	uint8_t state_sw3 = 0;
	static State_t current_state = Apagado;			// Estado inicial del sistema

	PIT_delay(PIT_0, SYSTEM_CLOCK, Delay_Password);
	PIT_delay(PIT_1, SYSTEM_CLOCK, Delay_Password);

	while (1) {

		state_sw2 = GPIO_get_irq_status(GPIO_C);	// Se lee si se presiono SW2



		if (state_sw2) {
			GPIO_clear_irq_status(GPIO_C);
		}

		switch (current_state) {
		case Apagado:
			if (intento) {
				current_state = waitSELECT_PROCESO;
				printf("\nCLAVE_MAESTRA correcta!");
				GPIO_set_pin(GPIO_B, bit_18); /** Power On: GREEN LED */
			}
			break; // end case waitCLAVE_MAESTRA

		case stop_MOTOR:
			g_FSM_status_flags.flag_FSM_MOTOR = FALSE;// Desactivacion de FSM Motor
			current_state = waitSELECT_PROCESO;
			break;	// end case stop_MOTOR

		default:
			break;
		} //end switch(current state)




		state_sw3 = GPIO_get_irq_status(GPIO_A);	// Se lee si se presiono SW3



	}
	return 0;

}
