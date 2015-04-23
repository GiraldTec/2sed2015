/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"


/*--- funciones externas ---*/
extern void buttons_init();
extern void keyboard_init();
extern void D8Led_init();
extern void leds_off();

extern void t0_init();
extern void t1_init();
extern void t2_init();

extern void set_estado(int estado);

//Declarar funciones externas de inicialización
/*--- declaracion de funciones ---*/
void Main(void);
void automata_init();

/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	//timer_init(); // Inicializacion del temporizador
	//// Inicialización del teclado matricial
	automata_init(); // equivalente a cambiar_estado(0)
	set_estado(0);

	while (1); // espera
}

void automata_init()
{
	buttons_init();		// CONFIGURAMOS LAS INTERRUPCIONES DE BOTONES
	keyboard_init();	// CONFIGURAMOS LAS INTERRUPCIONES DE TECLADO
	D8Led_init();		// INICIALIZAMOS 8LED
	leds_off();			// INICIALIZAMOS LEDS

	t0_init();			// CONFIGURAMOS LAS INTERRUPCIONES DE TIMER0
	t1_init();			// CONFIGURAMOS LAS INTERRUPCIONES DE TIMER1
	t2_init();			// CONFIGURAMOS LAS INTERRUPCIONES DE TIMER2
}
