//DEFINE MAIN HEADER FILE
#ifndef MAIN_H
#define MAIN_H

#include <includes.h>

//DEFINE PORTS/PINS
#define IR_SEN1_PIN			P1_0
#define IR_SEN2_PIN			P1_1

#define ENG_RLY_PIN			P0_2
					 	

//DEFINE CONSTANT
#define DTIME					10
#define MSG_WAIT_MSG			1
#define MSG_PH_NUM				2
#define MSG_COLL_MSG			3
#define MSG_RCV_MSG				4

#define LINE_FEED				0x0A

//DEFINE MACROS
#define vehistop()		 	ENG_RLY_PIN = LOW
#define vehirel() 			ENG_RLY_PIN = HIGH

#define starttmr()			TR0 = HIGH
#define stoptmr()			TR0 = LOW

#define EnUARTInt()			ES = 1
#define DisUARTInt()		ES = 0

//FUNCTION PROTOTYPES
static 	void 	init		(void);
static 	void 	disptitle	(void);
static 	void	tmrinit		(void);
static 	int8u	verpass 	(void);
static 	void 	dispscrn	(void);

#endif