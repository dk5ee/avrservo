
#ifndef TIMER1_H_
#define TIMER1_H_
#include <avr/io.h>
#include <avr/interrupt.h>

void   set_servo1(uint16_t duration);
void   set_servo2(uint16_t duration);
void   set_timertop(uint16_t duration);

void servo_enable();
void servo_dissable();

#endif /* TIMER1_H_ */
