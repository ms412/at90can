/*
 * gpio.cpp
 *
 *  Created on: 20.05.2013
 *      Author: markus
 */
#include "gpio.hpp"
#include <avr/io.h>


GPIO::GPIO(char reg, char pin){
		m_bit = _BV(pin);			// Get the bit mask for this port
		m_valid = true;				// assume constructor port/in is valid

		switch (reg)
		{
		case 'b':case 'B':
			m_dataDir = &DDRB;
			m_pin = &PINB;
			m_port = &PORTB;
			break;
		case 'c':case 'C':
			m_dataDir = &DDRC;
			m_pin = &PINC;
			m_port = &PORTC;
			break;
		case 'd':case 'D':
			m_dataDir = &DDRD;
			m_pin = &PIND;
			m_port = &PORTD;
			break;
		default:
			m_valid = false;
		}
	};

void GPIO::SetInput(){
	if(m_valid){
		*m_dataDir &= ~m_bit;
	}
};

void GPIO::SetOutput(){
	if(m_valid){
		*m_dataDir |= m_bit;
	}
};







