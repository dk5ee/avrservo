/*
	Licence MIT or do what you want..
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "servos.h"

int main(void) {
	DDRB |= (1<<5); // here is a led
	servo_enable();

	while (1) {
		//PORTB |= (1<<5);
		set_servo1(3500);
		set_servo2(3500);
		_delay_ms(500);
		//PORTB &= ~(1<<5);
		set_servo1(2500);
		set_servo2(2500);
		_delay_ms(500);
	}
	return 0;
}
