/*
 * uart1.cpp
 *
 *  Created on: 20.05.2013
 *      Author: markus
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../utils/fifo.hpp"
#include "uart1.hpp"

static CBuffer<uint8_t,20> TxBuffer;
static CBuffer<uint8_t,20> RxBuffer;

bool Uart1::read(uint8_t &c)
{
	if (RxBuffer.isEmpty()) {
		return false;
	}
	else {
		RxBuffer.Get(c);
	}
	return true;
}

bool Uart1::write(uint8_t c)
{
	if (!TxBuffer.isFull()){
		TxBuffer.Put(c);

		UCSR1B |= (1 << UDRIE1);

	}else{
		return false;
	}
return true;
}

ISR(USART1_UDRE_vect)
{
	cli();
	uint8_t c;
	if (!TxBuffer.isEmpty()){
		TxBuffer.Get(c);
		UDR1 = c;
	}else{
		UCSR1B &= ~(1 << UDRIE);
	}
	sei();
}

ISR(USART1_RX_vect)
{
	cli();
	uint8_t data = UDR1;
	RxBuffer.Put(data);
	sei();
}



