/* uart.c: uart interface program  */
#include"uart.h"
void uartinit(void){	      // INITIALIZE SERIAL PORT
		SCON 		= 0x50;			      		// SERIAL MODE 1, 8-DATA BIT 1-START BIT, 1-STOP BIT, REN ENABLED
		RCAP2H 	= 0xFF;					
		RCAP2L 	= 0xDC;					/* 0xDC: 9600, FA: 57600 */
		T2CON 	= 0x34;					/* Enable TCLK, RCLK, start tmr */
}
void putch(int8u serialdata){ 
	SBUF = serialdata;			// LOAD DATA TO SERIAL BUFFER REGISTER
	while(TI == 0);				// WAIT UNTIL TRANSMISSION TO COMPLETE
	TI = 0;					// CLEAR TRANSMISSION INTERRUPT FLAG
}
int8u getch(void){
	while(RI == 0);				// WAIT UNTIL DATA IS RECEIVED 
	RI = 0;					// CLEAR FLAG
	return SBUF;				// RETURN SERIAL DATA
}
void putstr(int8u *s){
	while(*s) putch(*s++);
}
