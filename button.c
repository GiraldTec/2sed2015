/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
int symbol;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void buttons_ISR(void) __attribute__ ((interrupt ("IRQ")));
void buttons_init(void);
extern void D8Led_symbol(int value);
extern void led1_on(); // LED 1 encendido
extern void led1_off(); // LED 1 apagado
extern void led2_on(); // LED 2 encendido
extern void led2_off(); // LED 2 apagado

/*--- codigo de funciones ---*/
void b_init(void)
{
/* Configuracion del controlador de interrupciones */
	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND = 0xf;

	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = BIT_EINT4567;

	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;		// tiene 26 bits

	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = 0x1<<0 ;	// tiene 4 bits, usamos 3 (X-Vectorizado-IRQ-FIQ)

	// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
	rINTMSK = ~(0x0); // Enmascaramos todas las interrupciones
	rINTMSK &= ~(0x1<<26); //Desenmascarar el global
	rINTMSK &= ~(BIT_EINT4567); //Desenmascarar el EINT4567


	// Establecer la rutina de servicio para Eint4567
	pISR_EINT4567=(unsigned)buttons_ISR;

/* Configuracion del puerto G */
	// Establece la funcion de los pines (EINT7-EINT0)
	rPCONG = 0xf<<12;	// Todos los pines del puerto G configurados para EINT?  // Tiene 16 bits

	//Habilita las resistencias de pull-up
	rPUPG = 0x3f;		// Como todos los pines son EINT? -> Habilitamos todas las resistencias de pull-up	// Tiene 8 bits

	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT &= ~(0x1 << 30);
	rEXTINT &= ~(0x1 << 26);
	rEXTINT |= (0x1<<29)|(0x1<<25);		// A pesar de que los demás pines están configurados esto

/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rEXTINTPND = 0xf;
	rI_ISPC = BIT_EINT4567;
}

int which_int;
void buttons_ISR(void)
{
	/*Identificar la interrupcion*/
	which_int = rEXTINTPND;
	/* Actualizar simbolo*/
	switch (which_int) {
		case 4 :  	// EINT6 IZQUIERDA Pausar
			// inhabilitar timers
			// inhabilitar teclado

			break;
		case 8 :	// EINT7 DERECHA	Reanudar
			// habilitar timers
			// habilitar teclado

			// inhabilitar botones

			break;
	}

	// espera 100ms para evitar rebotes
	DelayMs(100);

	// borra los bits en EXTINTPND  
	// borra el bit pendiente en INTPND
	rEXTINTPND = 0xf;
	rI_ISPC = BIT_EINT4567;
}

