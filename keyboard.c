/*--- Ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include "def.h"
/*--- Definición de macros ---*/
#define KEY_VALUE_MASK 0xF
/*--- Variables globales ---*/
volatile UCHAR *keyboard_base = (UCHAR *)0x06000000;
int key;
/*--- Funciones externas ---*/
void D8Led_symbol(int value);
void cambiar_estado(int key);

/*--- Declaracion de funciones ---*/
void keyboard_init();
void KeyboardInt(void) __attribute__ ((interrupt ("IRQ")));

/*--- Codigo de las funciones ---*/
void keyboard_init()
{
	/* Configurar el puerto G (si no lo estuviese ya) */	
	rPCONG = 0xffff;	// Establece la funcion de los pines (EINT0-7)
	rPUPG  = 0x0;		// Habilita el "pull up" del puerto
	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
		// fuerzo 0's
		rEXTINT &= ~(0x01<<30) & ~(0x01<<26) & ~(0x01<<22) & ~(0x01<<18) & ~(0x01<<14) & ~(0x01<<10) & ~(0x01<<6) & ~(0x01<<2);
		// fuerzo 1's
		rEXTINT |= (0x01<<29) | (0x01<<25) | (0x01<<21) | (0x01<<18) | (0x01<<14) | (0x01<<9) | (0x01<<5) | (0x01<<1);	
	
	/* Establece la rutina de servicio para EINT1 */
	pISR_EINT1=(unsigned)KeyboardInt;
	
	/* Configurar controlador de interrupciones */
	rI_ISPC=0x3ffffff;	// Borra INTPND escribiendo 1s en I_ISPC
	rINTMOD=0x0;		// Configurar las lineas como de tipo IRQ	
	rINTCON=0x1;		// Habilitar int. vectorizadas y la linea IRQ (FIQ no)	
	
	/* Habilitar linea EINT1 */
	rINTMSK = rINTMSK & ~(BIT_EINT1 | BIT_GLOBAL);

	/* Por precaucion, se vuelven a borrar los bits de INTPND correspondientes*/
	rI_ISPC=0x3ffffff;
}
void KeyboardInt(void)
{
	/* Esperar trp mediante la funcion DelayMs()*/
	Delay(200);
	/* Identificar la tecla */
	key = key_read();
	/* Si la tecla se ha identificado, visualizarla en el 8SEG*/
	if(key > -1){
		//D8Led_symbol(key);
		set_estado(key+1);
	}
	/* Esperar a se libere la tecla: consultar bit 1 del registro de datos del puerto G */
	while (rPDATG & (0x1<<1)){
		//NOTHING
	}
	/* Esperar trd mediante la funcion Delay() */
	Delay(1000);
	/* Borrar interrupción de teclado */
	rI_ISPC = BIT_EINT1;
}
int key_read()
{
	int value= -1;
	int aux = 0xf;
	char temp = 0xf;
	// Identificar la tecla mediante ''scanning''
	int i = 0;
	while(i<4 && aux == 0xf){
		switch (i){
			case 0: aux=*(keyboard_base + 0xfd); break;
			case 1:	aux=*(keyboard_base + 0xfb); break;
			case 2: aux=*(keyboard_base + 0xf7); break;
			case 3:	aux=*(keyboard_base + 0xef); break;
		}
		if(aux == 0xf) i++;	
	}
	
	temp = aux;
	temp &= KEY_VALUE_MASK;

	// Si la identificación falla la función debe devolver -1
	//temp = *(keyboard_base + 0xfd) & KEY_VALUE_MASK;
	//Usamos KEY_VALUE_MASK para quedarnos con los 4 bits menos significativos

	switch (temp) {
		case 0x7:  value = 4*i + 0; break;
		case 0xB:  value = 4*i + 1; break;
		case 0xD:  value = 4*i + 2; break;
		case 0xE:  value = 4*i + 3; break;
	}

	return value;

}
