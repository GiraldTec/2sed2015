/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
/*--- funciones externas ---*/
void D8Led_segments(int value);
/*--- declaracion de funciones ---*/
void timer01_ISR(void) __attribute__ ((interrupt ("IRQ")));
void t0_init(int hor);
void t1_init(int hor);
void t2_init(int hor);

int horario;
int estado;
int timer;


void t0_init(int hor){

	horario = hor;
	estado = 0;
	timer = 0;

	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
	rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global


	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0=(unsigned)timer01_ISR;


	/* Configurar el Timer0 cada 1.0s (el resto de los timers se dejan a la configuración por defecto) */
	rTCFG0=0xFF;// pre-escalado = 255
	rTCFG1 &= 0xFFFFF1;// divisor = 1/4
	//rTCFG1 |= 0x000002;
	rTCNTB0=65535;
	rTCMPB0=12800;

	rTCON=rTCON| (0x01<<1);// establecer manual_update
	rTCON=rTCON & ~(0x01<<1);// DESACTIVA manual_update
	rTCON=rTCON|(0x01<<3);//activar modo auto-reload

	rTCON=rTCON|(0x01<<0);// iniciar timer
}

void t1_init(int hor){

	horario = hor;
	estado = 0;
	timer = 1;

	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
	rINTMSK = rINTMSK & ~(BIT_TIMER1 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global


	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER1=(unsigned)timer01_ISR;


	/* Configurar el Timer1 cada 0.5s (el resto de los timers se dejan a la configuración por defecto) */
	rTCFG0=0xFF;// pre-escalado = 255
	rTCFG1 &= 0xFFFF0F;// divisor = 1/2
	//rTCFG1 |= 0x000002;
	rTCNTB1=65535;
	rTCMPB1=12800;

	rTCON=rTCON| (0x01<<9);// establecer manual_update
	rTCON=rTCON & ~(0x01<<9);// DESACTIVA manual_update
	rTCON=rTCON|(0x01<<11);//activar modo auto-reload

	rTCON=rTCON|(0x01<<8);// iniciar timer
}

void timer01_ISR(void){

	if(horario){
		estado++;
	}else{
		estado--;
	}
	estado = estado % 6;

	D8Led_segments(estado);

	switch (timer){
	case 1:
		rI_ISPC = BIT_TIMER1;
		break;
	default:
		rI_ISPC = BIT_TIMER0;
		break;
	}


}
