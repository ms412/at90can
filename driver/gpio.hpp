/*
 * gpio.hpp

 *
 *  Created on: 20.05.2013
 *      Author: markus
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#include <avr/io.h>


class GPIO
{
public:
	/* constructor for setting the register ('A', 'B', etc) and pin (0-7) */
	GPIO(char reg, char pin);

	inline uint8_t GetBit() const {return m_bit;};
	inline bool IsValid() const {return m_valid;};
	void SetInput();
	void SetOutput();

	void SetHigh() const{m_set(true);};
	void SetLow() const{m_set(false);};  //set output low
	void Toggle() const{if(IsValid()){*m_port ^= m_bit;};};  // toggle Output

	bool IsHigh() const{
			return (IsValid()) ? *m_port & m_bit :false;
		}

	inline bool IsLow() const { return !IsHigh(); };

protected:
	// The bit mask for this pin
	uint8_t				m_bit;


	// The PIN register
	volatile uint8_t*	m_pin;

	// The port register
	volatile uint8_t*	m_port;

	// The data direction register
	volatile uint8_t*	m_dataDir;

	// Does the constructor define a valid pin
	bool		m_valid;

	void m_set(bool high) const{
		if(IsValid()){
			if (high)
				*m_port |= m_bit;
			else
				*m_port &= ~m_bit;
		}
	};
};





#endif /* GPIO_HPP_ */
