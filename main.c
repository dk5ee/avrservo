/*
	Licence MIT or do what you want..
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "servos.h"

void blinki(uint8_t c) {
	cli();
	while (1) {
		for (uint8_t i=0; i<c;i++) {
			PORTB |= (1<<5);
			_delay_ms(100);
			PORTB &= ~(1<<5);
			_delay_ms(200);
		}
		_delay_ms(1000);
	}
}

int main(void) {
	DDRB |= (1<<5); // here is a led
	servo_enable();
	while (1) {
		PORTB |= (1<<5);
		set_servo1(3500);
		set_servo2(3500);
		_delay_ms(500);
		PORTB &= ~(1<<5);
		set_servo1(2500);
		set_servo2(2500);
		_delay_ms(500);
	}
	return 0;
}
