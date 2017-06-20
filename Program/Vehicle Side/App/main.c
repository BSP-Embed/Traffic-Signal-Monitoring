/* main.c:	application program for overloaded vehicle detection */
#include "main.h"
/* comment below line for release */
#define TESTING

#ifdef TESTING
	code const int8u RTOPhNum[] = "9980237552";
#else
	code const int8u RTOPhNum[] = "9916161778";
#endif

code const int8u RTOmsg[] = "<REL>";
code const int8u GSM_VIO_MSG[] = "Traffic Signal Violated By KA09-EV7397, Anusha Bellur.N";

int8u idata sbuf[100];
int8u idata phnum[15];

bit sigflag = 0;
bit sflag = 0;
bit sensflag = TRUE;
bit RELflag = TRUE;

int16u resp_tick = 0;

void main(void)
{								
	
	init();
	
	
	while (TRUE) {
		
		if (IR_SEN1_PIN == HIGH) {
			if (sensflag == TRUE) {
				lcdr2();
				lcdws("Stop Line1 Vio");
				sensflag = FALSE;
			}
			beep(2, 100);
		} else {
			if (sensflag == FALSE) {		
				dispscrn();
				sensflag = TRUE;
			}
		}


		if (IR_SEN2_PIN == HIGH && RELflag == TRUE) {
				/* msg to stop vehic */
				sigflag = 1;
				lcdclr();
				lcdws("Signal Violated!");
				lcdr2();
				lcdws(" Vehi Will Stop");
				buzon();
				DisUARTInt();
				EA = 0;	
				GSMsndmsg(RTOPhNum, GSM_VIO_MSG);
				buzoff();
				dispscrn();
				RI = 0;
				EnUARTInt();
				EA = 1;
				RELflag = FALSE;
		}

		if (sflag == 1) {
			EA = 0;
			sflag = 0;
			lcdclr();
			lcdws("Message Received");
			lcdr2();
			beep(1,100);
			dlyms(500);	
			switch (verpass()) {
				case 1: 
						lcdws("Vehicle Released");
						vehirel();
						RELflag = TRUE;
						break;
				default:
						lcdws("  Not Verified");
						break;
			} 
			dlyms(1000);
			RI = 0;
			EnUARTInt();
			EA = 1;
			dispscrn();
		}
	}
}
static int8u verpass (void)
{
	int8u i;
	for (i = 0; RTOmsg[i] != '\0'; i++) 
			if (RTOmsg[i] != sbuf[i])
					return 0;
 return 1;
}

static void disptitle(void)
{
	lcdclr();
	lcdws("Traffic Violat'n");
	lcdr2();
	lcdws("Monit & Alert'g");
}
static void dispscrn(void) 
{
	lcdclr();
	lcdws(" SMART VEHICLE");
}

static void init(void)
{
	beep(2,75);
	lcdinit();			  //initialize LCD
	uartinit();
	GSMinit();			 //GSM initialized
	disptitle();
	tmrinit();
	starttmr();
	EnUARTInt();
	dlyms(1000);
	dispscrn();
}
 
static void tmrinit(void)
{
	TMOD = TMOD & 0xf0 | 0x01;
	TH0 = 0x4B;
	TL0 = 0xFD;
	EA = ET0 = 1;
}
/* overflow every 50ms */

static void tmr0ISR() interrupt 1 using 1
{
	static int8u i,j,k;
	TH0 = 0x4B;
	TL0 = 0xFD;
	if (++i >= 2) {
		i = 0;
		if (++j >= 20) j = 0;
		switch (j) {
			case 0: case 2: ledon(); break;
			case 1: case 3: ledoff(); break;
		}
	}
	if (sigflag == 1 && ++k >= 250) { 
		vehistop();
		sigflag = 0;
		k = 0;
	}	
} 
void UARTISR(void) interrupt 4 using 3
{
	static int8u i;
	static int8u msgcnt,phcnt;
	static int8u state = MSG_WAIT_MSG;

	if (RI == 1) {
		RI = 0;
		switch (state) {
			case MSG_WAIT_MSG:
				if (SBUF == '\"') state = MSG_PH_NUM;
				break;
			case MSG_PH_NUM:
				if (phcnt++ < 13) 
					phnum[phcnt-1] = SBUF;
				else
					state = MSG_COLL_MSG;
				break;
			case MSG_COLL_MSG:
				if (SBUF == LINE_FEED)
					state = MSG_RCV_MSG;
				break;
			case MSG_RCV_MSG:
				if ((sbuf[msgcnt++] = SBUF) == LINE_FEED) {
					sbuf[msgcnt-2] = '\0';
					for (i = 0 ; i < 10; i++)	/* eliminate +91 */
						phnum[i] = phnum[i+3];
					phnum[i] = '\0';
					state = MSG_WAIT_MSG;
					msgcnt = 0;
					phcnt = 0;
					sflag = 1;
					DisUARTInt();
				}
		}
	}
}


	
	
