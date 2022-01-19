/*
 * KEYPAD_AVR.c
 *
 * Created: 3/01/2022 21:33:23
 * Author : alexb
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "DEF_ATMEGA328P.h"
#include "LCD.h"

#define COLUMNA1	PINCbits.PINC0_
#define COLUMNA2	PINCbits.PINC1_
#define COLUMNA3	PINCbits.PINC2_
#define COLUMNA4	PINCbits.PINC3_

#define FILA1		PORTBbits.PB0_
#define FILA2		PORTBbits.PB1_
#define FILA3		PORTBbits.PB2_
#define FILA4		PORTBbits.PB3_
#define LCD_INST	0;

uint8_t contador;
unsigned char tabla[16]={
	'1', '2', '3', 'A',
	'4', '5', '6', 'B',
	'7', '8', '9', 'C',
	'*', '0', '#', 'D' };
char inicio[] = "GRUPO 5 ";
char prr[] = "TEAM BMS ";



void KEYPAD_init(void)
{
	
	DDRBbits.DDRB0 = 1;
	DDRBbits.DDRB1 = 1;
	DDRBbits.DDRB2 = 1;
	DDRBbits.DDRB3 = 1;
	
	DDRCbits.DDRC0 = 0;
	DDRCbits.DDRC1 = 0;
	DDRCbits.DDRC2 = 0;
	DDRCbits.DDRC3 = 0;
	
	PORTCbits.PC0_ = 1;
	PORTCbits.PC1_ = 1;
	PORTCbits.PC2_ = 1;
	PORTCbits.PC3_ = 1;
	
}

uint8_t COLUMNA_scan(void)
{

	if(COLUMNA1 == 0)
	{
		while(COLUMNA1 == 0 || COLUMNA2 == 0 || COLUMNA3 == 0 || COLUMNA4 == 0);
		return 1;
	}
	contador++;
	
	if(COLUMNA2 == 0)
	{
		while(COLUMNA1 == 0 || COLUMNA2 == 0 || COLUMNA3 == 0 || COLUMNA4 == 0);
		return 1;
	}
	contador++;
	
	if(COLUMNA3 == 0)
	{
		while(COLUMNA1 == 0 || COLUMNA2 == 0 || COLUMNA3 == 0 || COLUMNA4 == 0);
		return 1;
	}
	contador++;
	
	if(COLUMNA4 == 0)
	{
		while(COLUMNA1 == 0 || COLUMNA2 == 0 || COLUMNA3 == 0 || COLUMNA4 == 0);
		return 1;
	}
	contador++;
	
	return 0;
	
}


void FILA_init(uint8_t fila)
{
	FILA1 = 1;
	FILA2 = 1;
	FILA3 = 1;
	FILA4 = 1;
	
	switch(fila)
	{ 
		case 1: FILA1 = 0; break;
		case 2: FILA2 = 0; break;
		case 3: FILA3 = 0; break;
		case 4: FILA4 = 0; break;
	}
	asm("NOP");	
}

uint8_t KEYPAD_read(void)
{
	_delay_ms(10);
	contador= 0;
	
	//Barrido de fila1
	FILA_init(1);
	if(COLUMNA_scan())
		return tabla[contador];

	//Barrido de fila2
	FILA_init(2);
	if(COLUMNA_scan())
		return tabla[contador];
	
	//Barrido de fila3
	FILA_init(3);
	
	if(COLUMNA_scan())
		return tabla[contador];

	//Barrido de fila4
	FILA_init(4);
	if(COLUMNA_scan())
		return tabla[contador];
	
	return 0;
	
}

int main(void)
{
	LCD_init();	
	KEYPAD_init();
	
	LCD_clear();
	LCD_home();
	LCD_printf("PROY. EMBEBIDOS");
	_delay_ms(1000);
	LCD_clear();
	LCD_home();
	LCD_printf(inicio);
	LCD_printf(prr);
	_delay_ms(1000);
	LCD_clear();
	LCD_home();
	LCD_printf("INGRESE SU NUMERO:");	
	_delay_ms(1000);
	LCD_clear();
	LCD_home();
	LCD_cursor(ON);
	
    /* Replace with your application code */
    while (1) 
    {
		
		uint8_t dato = KEYPAD_read();
		if (dato != 0)
			LCD_dato(dato);
		
    }
}

