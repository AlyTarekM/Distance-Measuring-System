/*
 * main.c
 *
 *  Created on: 14 Oct 2022
 *      Author: Aly Tarek
 */

#include "ultra.h"
#include "lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){

	uint16 distance=0;
	SREG|=(1<<7);
	/*
	 * Initialize both LCD and Ultrasonic
	 */
	LCD_init();
	Ultrasonic_init();

	LCD_displayString("Distance =    Cm");

	while(1){
		distance= Ultrasonic_readDistance();
		LCD_moveCursor(0, 11);
		LCD_intgerToString(distance);

		_delay_ms(100);
	}
	return 0;
}
