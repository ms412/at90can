/*
 * can_drv.cpp
 *
 *  Created on: 22.05.2013
 *      Author: Daniel
 */

#include "can_drv.hpp"

	bool Can0::Baudrate(uint8_t baudrate)
	{
	#if F_CPU	== 16000000
	switch(baudrate){
		case CAN_BAUDRATE_1000K:
			CANBT1		= 0x00;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return true;
			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return true;
			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x06;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return true;
			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x08;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return true;
			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x0e;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x12;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_50K:
			CANBT1		= 0x0E;
			CANBT2		= 0x0c;
			CANBT3		= 0x4C;
			return 1;
			break;

		default:
			return 0;
			break;
	}
#elif F_CPU	== 12000000
	switch(baudrate){
		case CAN_BAUDRATE_1000K:
			CANBT1		= 0x00;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			return 1;
			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x02;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			return 1;
			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x04;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x04;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			return 1;
			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x0a;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x0a;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			return 1;
			break;

		default:
			return 0;
			break;
	}
#elif F_CPU	==  8000000
	switch(baudrate){
		case CAN_BAUDRATE_1000K:
			CANBT1		= 0x00;
			CANBT2		= 0x04;
			CANBT3		= 0x13;
			return 1;
			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x00;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x02;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			return 1;
			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x06;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x08;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		default:
			return 0;
			break;
	}
#elif F_CPU	==  6000000
	switch(baudrate){
		case CAN_BAUDRATE_1000K:
			return 0;
			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x00;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			return 1;
			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x02;
			CANBT2		= 0x08;
			CANBT3		= 0x25;
			return 1;
			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x35;
			return 1;
			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x04;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x04;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			return 1;
			break;

		default:
			return 0;
			break;
	}
#elif F_CPU	==  4000000
	switch(baudrate){
		case CAN_BAUDRATE_1000K:
			return 0;
			break;

		case CAN_BAUDRATE_500K:
			CANBT1		= 0x00;
			CANBT2		= 0x04;
			CANBT3		= 0x13;
			return 1;
			break;

		case CAN_BAUDRATE_250K:
			CANBT1		= 0x02;
			CANBT2		= 0x04;
			CANBT3		= 0x13;
			return 1;
			break;

		case CAN_BAUDRATE_200K:
			CANBT1		= 0x00;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			return 1;
			break;

		case CAN_BAUDRATE_125K:
			CANBT1		= 0x02;
			CANBT2		= 0x0c;
			CANBT3		= 0x37;
			return 1;
			break;

		case CAN_BAUDRATE_100K:
			CANBT1		= 0x02;
			CANBT2		= 0x0e;
			CANBT3		= 0x4b;
			return 1;
			break;

		default:
			return 0;
			break;
	}
#else
	#warning F_CPU has no correct frequency for baudrate settings
	return 0;
#endif
}

