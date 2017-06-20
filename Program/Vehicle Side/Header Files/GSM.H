#ifndef GSM_H
#define GSM_H

//INCLUDE HEADER FILES
#include "includes.h"

//MACROS
#define EnZIG()		GSM_ZIG_PIN = LOW
#define EnGSM()		GSM_ZIG_PIN = HIGH

//FUNCTION PROTOTYPES	
		void 	GSMsndmsg			(int8u *PhNum, int8u *GSMMsg);
		bit 	GSMinit				(void);
static 	void 	GSMerr				(void);
static 	bit 	GSMRxResp			(void);
static 	bit 	GSMmsgparam			(void);
static 	bit 	GSMsndphnum			(int8u *PhNum);
static 	void	GSMrxack			(void);
		bit 	gsm_call_gen		(int8u *PhNum);
#ifdef GPS_LOC
	 	void 	GSMsendloc 			(int8u *PhNum);
#endif

#endif
