/*
 * @file:		Examen_1.c
 * @company:	ITESO
 * @Engineer:	D.F.R.
 */

#include <stdio.h>
#include "MK64F12.h"

// #define DEBUG_ON

int main(void) {

	SIM->SCGC5 = 0x400;			 // Enciendo bit #10 de "clock gating" del Port B.
	PORTB->PCR[22] = 0x00000100; // RED - Config. PCR en MUX como 001 - Alternative 1 (GPIO).
	GPIOB->PDOR = 0x00400000;	 // OFF - Antes de encender le asigno una valor lógico.
	GPIOB->PDDR = 0x00400000;	 // Output - Pongo el pin22 como salida.

	while (1) {
		GPIOB->PDOR = 0;		 // ON - Clear pin 22, el Led enciende.
#ifndef DEBUG_ON
		printf("RED LED ON\n");	 // printf solamente para debuggear (con el primer #define).
#endif

		GPIOB->PDOR = 0x00400000;// OFF - Los LEDs prenden con 0 y apagan con 1.

#ifndef DEBUG_ON
		printf("RED LED OFF\n");
#endif
	}
	return 0;

}
