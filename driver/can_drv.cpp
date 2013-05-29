/* can_drv.cpp
 *
 *  Created on: 22.05.2013
 *      Author: Daniel
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../utils/fifo.hpp"
#include "can_drv.hpp"

static CBuffer<struct MOb_struct,5> TxBuffer;
static CBuffer<struct MOb_struct,5> RxBuffer;

CAN t_CAN(CAN_BAUDRATE_125K);

CAN::CAN(uint8_t canspeed){

	uint8_t mob;

	CAN::Set_irq_state(false);

	CAN_RESET;

	//disable all CAN Interrupts
	CANIE1 = 0;
	CANIE2 = 0;

	//initial all mob objects
	for (mob = 0; mob < MAX_MOB; mob++)
	{
		SET_CANPAGE(mob);
		//CANPAGE  = (mob << 4);
		CANSTMOB = 0;
		CANCDMOB = 0;
	}

	// Set CAN interface speed
	if(set_canspeed(canspeed) == false)

	CANGIT = 0;

	//Enable Rx/Tx CAN interrupt
	CAN_RX_IRQ_ENABLE;
	CAN_TX_IRQ_ENABLE;

	//Enable global CAN interrupt
	CAN_IRQ_ENABLE;

	// Enable CAN subsystem
	CAN_ENABLE;

	//Wait until CAN is Ready
	loop_until_bit_is_set(CANGSTA, ENFG);
}

bool CAN::SetupMOb(uint8_t mob, uint8_t mode, uint32_t CAN_ID_Low, uint32_t CAN_ID_High)
{
	uint8_t temp_canpage;
	uint32_t maskId, canId;

	//verify that MOb is free
	if (mob > MAX_MOB){
		return false;
	}
	temp_canpage = CANPAGE;

	//select MOb
	SET_CANPAGE(mob);

	//enable interrupt for MOb
	MOB_IRQ_ENABLE(mob);

	//calculate and set mask
	maskId = ~(CAN_ID_High - CAN_ID_Low);
	SET_EXTENDED_MASK(maskId);

	//calculate and set CAN ID
	canId = (maskId & CAN_ID_Low);
	SET_EXTENDED_ID(canId);

	//enable interrupt of MOb
	MOB_IRQ_ENABLE(mob);

	switch(mode)
	{
	case DISABLED:
		MOb_DISABLE;
	break;

	case TX_DATA:
		MOb_ENABLE_TX;
	break;

	case RX_DATA:
		MOb_ENABLE_RX;
	break;

	default:
		return false;
	}

	CANPAGE = temp_canpage;

	return true;
}

//selects the CANPAGE of the MOb
bool CAN::get_MOb(uint8_t mob)
{
	CANPAGE = (mob << 4);

	return true;
}

bool CAN::put(struct MOb_struct *MOb)
{
	//PORTD ^= (1<<PD7);
	// if MOb is free
	//if buffer is empty, no Tx interrupt will occur
	if (Get_irq_state()){
		//PORTD ^= (1<<PD4);
		if (TxBuffer.isFull()){
			//PORTD ^= (1<<PD4);
			return false;
		}
		//MOb is in Buffer
		cli();
		RxBuffer.Put(*MOb);
		sei();
		return true;
	}
	Set_irq_state(true);
	PORTD ^= (1<<PD5);
	CAN::write(MOb);

	return true;
}

bool CAN::write(struct MOb_struct *MOb)
{
	uint8_t temp_canpage;
	//uint8_t i;
	//PORTD ^= (1<<PD7);

	temp_canpage = CANPAGE;
	SET_CANPAGE(MOb->number);

	CANSTMOB = 0x00;
	//CANCDMOB = 0x00;
	CANCDMOB |= (1<<IDE);

	SET_EXTENDED_ID(MOb->id);

	CANCDMOB |= MOb->length;

	for (uint8_t i=0; i < MOb->length; i++){
		CANMSG = MOb->data[i];
	}

	MOb_ENABLE_TX

	CANPAGE = temp_canpage;

	sei();
	return true;
}
bool CAN::status_MOb(uint8_t mob)
{
	//select MOb page
	SET_CANPAGE(mob);

	//check if MOb is in use
	if ((CANCDMOB & ((1<<CONMOB1)|(1<<CONMOB0)))==0){
		return true;
	}

	return false;
}

bool CAN::set_canspeed(uint8_t canspeed)
{
	#if F_CPU	== 16000000
	switch(canspeed){
		case CAN_BAUDRATE_1000K:
			CANBT1		= 0x00;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x06;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x08;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x0e;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x12;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_50K:
			CANBT1		= 0x0E;
			CANBT2		= 0x0c;
			CANBT3		= 0x4C;

			break;

		default:

			break;
	}
#elif F_CPU	== 12000000
	switch(canspeed){
		case CAN_BAUDRATE_1000K:
			CANBT1		= 0x00;
			CANBT2		= 0x08;
			CANBT3		= 0x25;

			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x02;
			CANBT2		= 0x08;
			CANBT3		= 0x25;

			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x04;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x04;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;

			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x0a;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x0a;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;

			break;

		default:

			break;
	}
#elif F_CPU	==  8000000
	switch(canspeed){
		case CAN_BAUDRATE_1000K:
			CANBT1		= 0x00;
			CANBT2		= 0x04;
			CANBT3		= 0x13;

			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x00;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x02;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;

			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x06;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x08;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		default:
			break;
	}
#elif F_CPU	==  6000000
	switch(canspeed){
		case CAN_BAUDRATE_1000K:
			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x00;
			CANBT2		= 0x08;
			CANBT3		= 0x25;

			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x02;
			CANBT2		= 0x08;
			CANBT3		= 0x25;

			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x35;

			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x04;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x04;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;

			break;

		default:
			break;
	}
#elif F_CPU	==  4000000
	switch(canspeed){
		case CAN_BAUDRATE_1000K:
			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x00;
			CANBT2		= 0x04;
			CANBT3		= 0x13;

			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x02;
			CANBT2		= 0x04;
			CANBT3		= 0x13;

			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x00;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;

			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;

			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x02;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;

			break;

		default:
			break;
	}
	#else
		#warning F_CPU has no correct frequency for canspeed settings
		return false;
	#endif

}



void CANIT_vect()
{
	//cli();
	uint8_t temp_canpage;
	uint8_t mob;



	if ((CANHPMOB & 0xf0) != 0xf0){


			//save current canpage setting
			temp_canpage = CANPAGE;

			//get first MOb with interrupt
			mob = (CANHPMOB >> 4);
			//select Canpage with interrupt
			SET_CANPAGE(mob);

			//if Rx interrupt is present
			if (CANSTMOB & (1<<RXOK)){
				//PORTD ^= (1<<PD7);
				//IRQ_Service_Rx(mob);
			}else if (CANSTMOB & (1<<TXOK)){  //TX interrupt
				CANSTMOB &= 0;
				CANCDMOB = 0;
				//IRQ_Service_Tx(mob);
				PORTD ^= (1<<PD7);
				t_CAN.Set_irq_state(true);
				struct MOb_struct MOb;
				if (!TxBuffer.isEmpty()){
					PORTD ^= (1<<PD4);
					TxBuffer.Get(MOb);
					t_CAN.write(&MOb);
				}else{
					t_CAN.Set_irq_state(false);
				}
		MOB_IRQ_DISABLE(mob);
			}
	//}else{			//error interrupt
		//IRQ_Service_Err(mob;)
	}else{
		CANGIT |=0;
		}
	CANPAGE = temp_canpage;
}
