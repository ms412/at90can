/*
 * fifo.hpp
 *
 *  Created on: 19.05.2013
 *      Author: markus
 */

#ifndef FIFO_HPP_
#define FIFO_HPP_

#define BUFFER_SIZE 32

template <class CBufferType, int BufferSize=32>

class CBuffer
{
public:
	//Constructor
	CBuffer(): m_put(0), m_get(0) {}

	bool isEmpty() {return (m_put == m_get);}
	bool isFull(){
		int temp = m_put;
		Inc(temp);
		return temp == m_get;
	}

	bool Get(CBufferType &Slot){
		if (isEmpty())
			return false;
		Slot = m_Slots[m_get];
		Inc(m_get);
		return true;
	}

	bool Put(const CBufferType &Slot){
		if (isFull())
			return false;
		m_Slots[m_put] = Slot;
		Inc(m_put);
		return true;
	}

private:
	CBufferType m_Slots[BufferSize+1];
	int m_put, m_get;
	void Inc (int & Pos) {Pos = (Pos+1)%(BufferSize+1);}

};


#endif /* FIFO_HPP_ */
