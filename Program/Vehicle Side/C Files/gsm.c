/* gsm.c:	interface program for GSM modem */
#include "gsm.h"

//GSM AT COMMANDS
code int8u ATCommand[] 		= "AT\r"; 
code int8u ATCall[]			= "ATD";
code int8u SMSCode[] 		= "AT+CMGF=1\r";
code int8u SMSNumber[] 		= "AT+CMGS=\"0";
code int8u SMSSettings[]	= "AT+CNMI=2,2,2,0,0\r";

void GSMsndmsg(int8u *PhNum, int8u *GSMMsg)
{
	#if GSM_LCD_EN > 0
		lcdclrr(1);
		lcdws("Sending SMS: ");
	#endif
	if(GSMsndphnum(PhNum)) {
		putstr(MSG_START);
		putstr(GSMMsg);
		putstr(MSG_END);
		putch(0x1A);
		GSMrxack();
	} else	GSMerr();
	#if  GSM_LCD_EN > 0
		lcdws("OK");
		dlyms(1000);
	#endif
}
bit GSMinit(void)
{
	#if  GSM_LCD_EN > 0
		lcdclrr(1);
		lcdws("Init GSM : ");
	#endif
	if(GSMRxResp() && GSMmsgparam() ) {
		#if GSM_LCD_EN > 0
			lcdws("OK");
			dlyms(1000);
		#endif
		return 1;
	} else {
		GSMerr();
		return 0;
  } 
}
static void GSMerr(void)
{
	 #if  GSM_LCD_EN > 0
		lcdr2();
	 	lcdws("FAILED !");
	#endif
}
static bit GSMRxResp(void) {
	putstr(ATCommand);
	while(getch() != 'K');
	return 1;
}
static bit GSMmsgparam(void){
	putstr(SMSCode);
  while(getch() != 'K');
	putstr(SMSSettings);
  while(getch() != 'K');
	return 1;
}
static bit GSMsndphnum(int8u *PhNum)
{
	putstr(SMSNumber);
	putstr(PhNum);
	putstr("\"\r");
	while (getch() != '>');
	return 1;
}
static void GSMrxack(void)
{
	int8u x;
	do {
	 	x = getch();
	 }while(x != 'K' && x != 'E');
	 if(x == 'E') if(!GSMRxResp()) GSMerr();
}
bit gsm_call_gen(int8u *PhNum)
{
	putstr(ATCall);
	putstr(PhNum);
	putstr(";\r");
	return 1;
}
#ifdef GPS_LOC
	void GSMsendloc (int8u *PhNum)
	{
		int8u idata i, GSMmsg[30], Lat[10], Lon[11];
	
		Lat[9]	= '\0';
	 	Lon[10]	= '\0';
		
		EnGPS();
		dlyms(500);
		GPSgetloc(Lat, Lon);
		EnGSM();
		dlyms(500);
		
		for(i = 0; i < 30; i++)
			GSMmsg[i] = '\0';
		
		strcat (GSMmsg, Lat);
		strcat (GSMmsg, ",LON:");
		strcat (GSMmsg, Lon);
		
		GSMsndmsg(PhNum, GSMmsg);
		
	}
#endif

