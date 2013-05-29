/*
 * can_driv.hpp
 *
 *  Created on: 22.05.2013
 *      Author: Daniel
 */

#ifndef CAN_DRIV_HPP_
#define CAN_DRIV_HPP_

#include <avr/io.h>


// ----- M A R K R O S -----

//CAN Enable
#define CAN_ENABLE			      {CANGCON |= (1<<ENASTB);}
//CAN Disable
#define CAN_STANDBY				  {CANGCON &= (~(1<<ENASTB);}
//CAN Reset
#define CAN_RESET			      {CANGCON = (1<<SWRES);}


/* Configure CAN Interrupte Sources */

//CAN General Interrupt
#define CAN_IRQ_ENABLE            { CANGIE |= (1<<ENIT); }		//Enable
#define CAN_IRQ_DISABLE           { CANGIE &= (~(1<<ENIT)); }   //Disable
//CAN Receive Interrupt
#define CAN_RX_IRQ_ENABLE         { CANGIE |= (1<<ENRX);  }		//Enable
#define CAN_RX_IRQ_DISABLE        { CANGIE &= (~(1<<ENRX)); }   //Disable
//CAN Transmitt Interrupt
#define CAN_TX_IRQ_ENABLE         { CANGIE |= (1<<ENTX);  }		//Enable
#define CAN_TX_IRQ_DISABLE        { CANGIE &= (~(1<<ENTX)); }   //Disable

//CANPAGE Set/Get
#define SET_CANPAGE(mob)		  (CANPAGE = (mob << 4))
#define GET_CANPAGE				  (CANPAGE >> 4)

//Enable/Disable interrupt for the mob
#define MOB_IRQ_ENABLE(mob)	  {(((mob) < (8))?(CANIE2 |= (1<<(mob))):(CANIE1 |= (1<<mob - 8)));}
#define MOB_IRQ_DISABLE(mob)  {(((mob) < (8))?(CANIE2 &= (~(1<<(mob)))):(CANIE1 &= (~(1<<mob - 8))));}

/* Set CAN identifier and mask */
//makro to split up 32bit into 4x8
#define CAN_SET_EXT_ID_28_21(identifier) (((*((uint8_t *)(&identifier)+3))<<3)+((*((uint8_t *)(&identifier)+2))>>5))
#define CAN_SET_EXT_ID_20_13(identifier) (((*((uint8_t *)(&identifier)+2))<<3)+((*((uint8_t *)(&identifier)+1))>>5))
#define CAN_SET_EXT_ID_12_5(identifier)  (((*((uint8_t *)(&identifier)+1))<<3)+((* (uint8_t *)(&identifier)   )>>5))
#define CAN_SET_EXT_ID_4_0(identifier)    ((* (uint8_t *)(&identifier)   )<<3)

//set extended CAN ID
#define SET_EXTENDED_ID(identifier) {\
        CANIDT1 = CAN_SET_EXT_ID_28_21 (identifier);\
        CANIDT2 = CAN_SET_EXT_ID_20_13 (identifier);\
        CANIDT3 = CAN_SET_EXT_ID_12_5  (identifier);\
        CANIDT4 = CAN_SET_EXT_ID_4_0   (identifier);\
        CANCDMOB |= (1<<IDE); }

//set extended CAN Mask
#define SET_EXTENDED_MASK(mask) {\
		CANIDM1 = CAN_SET_EXT_ID_28_21(mask);\
        CANIDM2 = CAN_SET_EXT_ID_20_13(mask);\
        CANIDM3 = CAN_SET_EXT_ID_12_5(mask);\
        CANIDM4 = CAN_SET_EXT_ID_4_0(mask);\
		CANIDM4 = (1<<IDEMSK);}

//SET MOb to Enable TX/RX,Disable
#define CONMOB_MSK 		((1<<CONMOB1)|(1<<CONMOB0))
#define MOb_Tx_ENA 1
#define MOb_Rx_ENA 2

#define MOb_DISABLE 	{CANCDMOB &= (~CONMOB_MSK);}
#define MOb_ENABLE_TX	{MOb_DISABLE; CANCDMOB |= (MOb_Tx_ENA << CONMOB0);}
#define MOb_ENABLE_RX	{MOb_DISABLE; CANCDMOB |= (MOb_Rx_ENA << CONMOB0);}

//#define MOb_DISABLE        { CANCDMOB &= (~(1<<CONMOB1));CANCDMOB &= (~(1<<CONMOB0));}
//#define MOb_ENABLE_TX      { CANCDMOB &= (~(1<<CONMOB1));CANCDMOB |= (1<<CONMOB0);}
//#define MOb_ENABLE_RX      { CANCDMOB |= (1<<CONMOB1);CANCDMOB &= (~(1<<CONMOB0));}

#define MOb_TX_IRQ		{CANSTMOB |= (1<<TXOK);}

#define MAX_MOB 15
  // canspeed
  enum { CAN_BAUDRATE_50K, CAN_BAUDRATE_100K, CAN_BAUDRATE_125K, CAN_BAUDRATE_200K,
         CAN_BAUDRATE_250K, CAN_BAUDRATE_500K, CAN_BAUDRATE_1000K };

  enum {DISABLED, TX_DATA, RX_DATA, TX_REMOTE, AUTO_REPLY};


  struct MOb_struct{
  	uint32_t id;
  	uint8_t number;
  	uint8_t length;
  	uint8_t data[8];
  };

  extern "C" void CANIT_vect(void) __attribute__ ((signal));

  extern class CAN t_CAN;

class CAN {
public:
	// constructor
	CAN(uint8_t canspeed);
	bool SetupMOb(uint8_t mob,  uint8_t mode, uint32_t CAN_ID_Low, uint32_t CAN_ID_High);
	bool write(struct MOb_struct *MOb);
	bool put(struct MOb_struct *MOb);

	// Flag monitors the current Tx Progress

	void Set_irq_state(bool state){irq_state = state;}
	bool Get_irq_state(void) {return irq_state;}


private:
	bool status_MOb(uint8_t mob);
	bool set_canspeed(uint8_t canspeed);
	bool get_MOb(uint8_t mob);
	uint8_t MOb_Signal_Act(void);

	friend void CANIT_vect();

	bool irq_state;





};

#endif /* CAN_DRIV_HPP_ */
