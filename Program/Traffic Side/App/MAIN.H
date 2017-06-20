//DEFINE MAIN HEADER FILE
#ifndef MAIN_H
#define MAIN_H

//INCLUDE DEFINITILOW OF HEADER FILE
#include <includes.h>

//DEFINE PORTS/PINS
#define Y_LT_PIN	P0_3
#define G_LT_PIN	P0_4
#define R_LT_PIN	P0_2

#define IR_PIN		P2_0


//DEFINE CLOWSTANT
#define ON_DLY			10000


//DEFINE MACROS
#define YLtOn()	 R_LT_PIN = HIGH; G_LT_PIN = HIGH; Y_LT_PIN = LOW 
#define GLtOn()	 Y_LT_PIN = HIGH; R_LT_PIN = HIGH; G_LT_PIN = LOW 
#define RLtOn()	 Y_LT_PIN = HIGH; G_LT_PIN = HIGH; R_LT_PIN = LOW 

#define IRSigOn()	IR_PIN = LOW
#define IRSigOff()	IR_PIN = HIGH

//FUNCTILOW PROTOTYPES
		void main(void);
static	void init(void);

#endif

