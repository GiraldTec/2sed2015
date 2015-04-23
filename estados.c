/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"

void configurarT0(int hor);
void configurarT1(int hor);
void configurarT2(int reps);


void set_estado(int key);

void set_estado(int key){
	switch(key){
	case 1:					// ANTIHORARIO VELOCIDAD X


		break;
	case 2:					// ANTIHORARIO VELOCIDAD 2X

		break;
	case 3:					// HORARIO VELOCIDAD X

		break;
	case 4:					// HORARIO VELOCIDAD 2X

		break;
	case 5:					// LEDS ALTERNAN FLASH 1
		// deshabilitar-borrar timers 1 y 0
		// flashes = 1
		// habilitar timer 2
		// iniciar timer 2


		break;
	case 6:					// LEDS ALTERNAN FLASH 2
		// deshabilitar-borrar timers 1 y 0
		// flashes = 2
		// habilitar timer 2
		// iniciar timer 2


		break;
	case 7:					// LEDS ALTERNAN FLASH 3
		// deshabilitar-borrar timers 1 y 0
		// flashes = 3
		// habilitar timer 2
		// iniciar timer 2


		break;
	case 8:					// LEDS ALTERNAN FLASH 4
		// deshabilitar-borrar timers 1 y 0
		// flashes = 4
		// habilitar timer 2
		// iniciar timer 2


		break;
	default: // caso 0 y del 8 al 15

		break;
	}
}

