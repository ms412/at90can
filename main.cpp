/*
 * main.cpp
 *
 *  Created on: 20.05.2013
 *      Author: markus
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "driver/uart0.hpp"
#include "driver/uart1.hpp"
#include "driver/timer2.hpp"
#include "driver/gpio.hpp"
#include "driver/can_drv.hpp"

int main(void)
{
	//char cmd[40];
	int counter = 0;
	uint32_t t_time;

	GPIO g_led ('B',7);
	g_led.SetOutput();
	CTimer2 rtc();
	Uart0 serial0(115200);
	Uart1 serial1(115200);
	Can0 can0(CAN_BAUDRATE_200K);
	can0.Baudrate(CAN_BAUDRATE_200K);

	sei();

	t_Timer2.get_timer(t_time);

	while(1){

		counter++;
		serial0.write('0x71');
		serial1.write(5);
		serial0.write(counter);
		serial1.write(counter);

		g_led.SetLow();
		_delay_ms(1000);
		g_led.SetHigh();
		_delay_ms(1000);
		g_led.IsHigh();
		g_led.Toggle();
		_delay_ms(2000);
	}

	return true;
}




