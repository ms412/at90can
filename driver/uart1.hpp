/*
 * uart1.hpp
 *
 *  Created on: 20.05.2013
 *      Author: markus
 */

#ifndef UART1_HPP_
#define UART1_HPP_

#include <avr/io.h>
#include "../utils/fifo.hpp"

#define UBRR_CALC(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*8l)-1)

class Uart1 {

public:
	// constructor
	Uart1(uint32_t baudrate){

	m_txByte = 0;
	m_rxByte = 0;
	m_error =0;

	UBRR1H = (unsigned char)(UBRR_CALC(baudrate,F_CPU) >> 8);
	UBRR1L = (unsigned char) UBRR_CALC(baudrate,F_CPU);

	UCSR1A = (1<<U2X0);

    /* Enable UART receiver and transmitter */
    UCSR1C |= (0<<UMSEL0) | (0<<UPM0) | (0<<USBS0) | (3<<UCSZ0);

	/* Enable UART receiver and transmitter */
    UCSR1B |= (1<<TXEN0) | (1<<RXEN0 | (1 << RXCIE0));
	};

    bool read(uint8_t &c);
	bool write(uint8_t c);

private:
	uint16_t m_txByte, m_rxByte, m_error;
	char m_buffer [sizeof(uint16_t)*8+1];
};





#endif /* UART1_HPP_ */
