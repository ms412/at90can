/*
 * timer2.hpp
 *
 *  Created on: 20.05.2013
 *      Author: markus
 */

#ifndef TIMER2_HPP_
#define TIMER2_HPP_

extern "C" void TIMER2_OVF_vect(void) __attribute__ ((signal));

extern class CTimer2 t_Timer2;

class CTimer2 {
public:
	CTimer2(void);
	void get_timer(uint32_t &time);
private:

	friend void TIMER2_OVF_vect();
	uint32_t m_time;
};


#endif /* TIMER2_HPP_ */
