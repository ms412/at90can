/*
 * timer2.cpp
 *
 *  Created on: 20.05.2013
 *      Author: markus
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer2.hpp"

//Timer2 Timer2;   // the CTimer0 instance

//-------------------------------------------------------------------
// The constructor provides all the required initialization for
// this device.
//

CTimer2 t_Timer2;

CTimer2::CTimer2(void){

	m_time = 0;

	cli();

	TIMSK2 |= (0<< TOIE2);
	ASSR   = (1<< AS2);

	TCNT2 = 0;              // clear TCNT2A
	TCCR2A |= (1<<CS22) | (1<<CS20);  // select prescaler: 32.768 kHz / 128 = 1 sec between each overflow


	while((ASSR & 0x01) | (ASSR & 0x04));       // wait for TCN2UB and TCR2UB to be cleared

	TIFR2 = 0xFF;           // clear interrupt-flags

	TIMSK2 |= (1<< TOIE2);
	};

void CTimer2::get_timer(uint32_t &time){

	time = m_time;
}

void TIMER2_OVF_vect() {

	t_Timer2.m_time++;
	//PORTB ^=(1<<PB7);
}



