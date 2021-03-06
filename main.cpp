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
	MOb_struct MOb;

	//Test
	DDRD = 0xff;

	GPIO g_led ('B',7);
	g_led.SetOutput();
	CTimer2 rtc();
	Uart0 serial0(115200);
	Uart1 serial1(115200);
//	CAN t_can(CAN_BAUDRATE_125K);
	t_CAN.SetupMOb(15,RX_DATA,0x0000000F,0x000000F0);
	t_CAN.SetupMOb(13,TX_DATA,0x0000000F,0x000000F0);
	t_CAN.SetupMOb(14,TX_DATA,0x0000000F,0x000000F0);
	//can.HwSetup(6);


	MOb.id=0x000000001;
	MOb.number = 14;
	MOb.length = 8;
	MOb.data[0]= 0x01;
	MOb.data[1]= 0x02;
	MOb.data[2]= 0x03;
	MOb.data[3]= 0x04;
	MOb.data[4]= 0x05;
	MOb.data[5]= 0x06;
	MOb.data[6]= 0x07;
	MOb.data[7]= 0x08;

	sei();

	t_Timer2.get_timer(t_time);

	while(1){
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		t_CAN.put(&MOb);
		//counter++;
		serial0.write('51');
		serial1.write(5);
		//serial0.write(counter);
		//serial1.write(counter);

	//	g_led.SetLow();
	//	_delay_ms(1000);
	//	g_led.SetHigh();
	//	_delay_ms(1000);
	//	g_led.IsHigh();
		g_led.Toggle();
		_delay_ms(1000);
	}

	return true;
}




