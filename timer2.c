/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
/*--- funciones externas ---*/
extern void leds_switch();
/*--- declaracion de funciones ---*/
void timer2_ISR(void) __attribute__ ((interrupt ("IRQ")));
void configurarT2(int reps);

int repeticiones;
int estado;

void configurarT2(int reps){

	repeticiones = reps;
	estado = 0;

	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
	rINTMSK = rINTMSK & ~(BIT_TIMER2 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global


	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER2=(unsigned)timer2_ISR;


	/* Configurar el Timer0 cada 1.0s (el resto de los timers se dejan a la configuración por defecto) */
	rTCFG0=(0xFF << 8);// pre-escalado = 255
	rTCFG1 &= 0xFFF0FF;// divisor = 1/2
	//rTCFG1 |= 0x000002;
	rTCNTB2=65535;
	rTCMPB2=12800;

	rTCON=rTCON| (0x01<<13);// establecer manual_update
	rTCON=rTCON & ~(0x01<<13);// DESACTIVA manual_update
	rTCON=rTCON|(0x01<<15);//activar modo auto-reload

	rTCON=rTCON|(0x01<<12);// iniciar timer
}

void timer2_ISR(void){

}
