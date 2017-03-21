#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <modes.h>
#include <types.h>
#include <cglob.h>
#include <module.h>

#include "MemData.h"

#define MEMORY_NAME "CommonMem"

sig_handler(signal_code sig)
	{	
	switch (sig)
		{
		case 400 : printf("P2: received a signal -	Case 400\n");
	 		break;
		
		case 500 : printf("P2:breceived a message from P4	Case 500\n");
		break;				   
	   }
	_os_rte();
	}


main()
	{

	error_code err;
	u_int32 num_ticks;
	signal_code dummy_sig;
	u_int16 attr_rev, type_lang;
	u_int16 mem_size;
	mh_com mod_head;
	signal_code DummySignal;
	u_int32 SleepTime;
	char *ptrMemName;
	int i;
	int testPID;
	struct MemData *CommonMem;


	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT << 8);

	if ((err = _os_intercept(sig_handler, _glob_data)) != 0)
		exit(err);

    SleepTime =	450;
	_os_sleep(&SleepTime, &DummySignal);
	
	ptrMemName = MEMORY_NAME;


	errno = _os_link(&ptrMemName, (mh_com**)&mod_head, (void **)&CommonMem, &type_lang, &attr_rev);

	num_ticks = 200;
	_os_sleep(&num_ticks, &dummy_sig);
 
	_os_send(CommonMem -> PID[3], 400);
	
	while (1) {
		 num_ticks = 500;
		_os_sleep(&num_ticks, &dummy_sig);
		}


}

