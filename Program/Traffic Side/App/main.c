/* main.c Main application program for traffic signal  */
# include "main.h"

void main(void)
{
		init();
		while (TRUE) {
			GLtOn();
			dlyms(ON_DLY);
			YLtOn();
			dlyms(ON_DLY / 4);
			RLtOn();
			IRSigOn();
			dlyms(ON_DLY*3);
			IRSigOff();
		}
 }
static void init(void)
{
	G_LT_PIN = INPUT_PIN;
	Y_LT_PIN = INPUT_PIN;
	R_LT_PIN = INPUT_PIN;
	IR_PIN = INPUT_PIN;	
}
