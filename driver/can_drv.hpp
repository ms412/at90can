/*
 * can_driv.hpp
 *
 *  Created on: 22.05.2013
 *      Author: Daniel
 */

#ifndef CAN_DRIV_HPP_
#define CAN_DRIV_HPP_

#include <avr/io.h>

  // baudrate
  enum { CAN_BAUDRATE_50K, CAN_BAUDRATE_100K, CAN_BAUDRATE_125K, CAN_BAUDRATE_200K,
         CAN_BAUDRATE_250K, CAN_BAUDRATE_500K, CAN_BAUDRATE_1000K };


class Can0 {

public:
	// constructor
	Can0(uint8_t canspeed){canspeed = CAN_BAUDRATE_125K;}

	bool Baudrate(uint8_t baudrate);


private:
	uint8_t t_canspeed;

};

#endif /* CAN_DRIV_HPP_ */
