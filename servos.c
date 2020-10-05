#include "servos.h"

volatile uint16_t servo1 = 0;
volatile uint16_t servo2 = 0;

//setservo - interrupt save
/*
 * prescaler == 8
 1ms..
 12mhz= 1500
 16mhz= 2000 <----
 20mhz= 2500
 25mhz= 3125

 2ms..
 12mhz= 3000
 16mhz= 4000 <----
 20mhz= 5000
 25mhz= 6250

 */

void inline set_servo1(uint16_t duration) {
	servo1 = duration;
}
void inline set_servo2(uint16_t duration) {
	servo2 = duration;
}
void set_timertop(uint16_t duration) {
	/*
	 * prescaler == 8
	 20ms is wanted => 50Hz
	 12mhz= 30000
	 16mhz= 40000 <----
	 20mhz= 50000
	 25mhz= 62500
	 */
	ICR1 = duration;
}

void servo_enable() {
	cli();
	DDRB |= (1 << PB1);
	DDRB |= (1 << PB2);
	//2. set defaults
	servo1 = 3000;
	OCR1A = 3000;
	servo2 = 3000;
	OCR1B = 3000;
	ICR1 = 40000;
	TCCR1A = 0;
	TCCR1B = 0;
	//WGM1= 1110 : Waveform Generation Mode 14 - Fast PWM

	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	//5. clear on compare, pb1 and pb2 output
	TCCR1A |= (1 << COM1A1) | (0 << COM1A0);
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0);
	//6. prescaler 8
	TCCR1B |= (0 << CS10) | (1 << CS11) | (0 << CS12);

	//7. change pwm duration on timer overflow interrupt
	TIFR1 |= (1<<TOV1);
	TIMSK1 |= (1 << TOIE1);
	TIMSK1 |= (1<<OCIE1A);
	TIMSK1 |= (1<<OCIE1B);
	sei();
}
void servo_dissable() {
	TIMSK1 &= ~(1 << TOIE1);
	DDRB &= ~(1 << PB1);
	DDRB &= ~(1 << PB2);
	//CS1 => 0 => dissable timer
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (0 << CS10) | (0 << CS11)
			| (0 << CS12);

}
ISR(TIMER1_OVF_vect) {
//	PINB |= (5<<PB1);
//	PORTB |= (1<<PB1);
//	PORTB |= (1<<PB2);
	OCR1A = servo1;
	OCR1B = servo2;
}
ISR ( TIMER1_COMPA_vect ) {
//	PORTB &= ~(1<<PB1);
}
ISR ( TIMER1_COMPB_vect ) {
//	PORTB &= ~(1<<PB2);
}
