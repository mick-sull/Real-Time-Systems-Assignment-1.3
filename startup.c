#include <stdio.h>
#include <signal.h>
#include <module.h>
#include <types.h>
#include <errno.h>
#include <stdio.h>
#include <errno.h>
#include <process.h>
#include <dexec.h>
#include <types.h>
#include <string.h>
#include <modes.h>
#include <cglob.h>

#include "MemData.h"

#define MEMORY_NAME "CommonMem"


main(int argc , char * argv[], char **envp)
	{

	u_int16 attr_rev, type_lang;
	u_int16	perm,mem_size;
	mh_com mod_head;
	signal_code dummy_sig;
	u_int32 num_ticks;

	error_code err;
	
	process_id p1_pid;
	process_id p2_pid;
	process_id p3_pid;
	process_id p4_pid;


	status_code child_statusP1;
	status_code child_statusP2;
	status_code child_statusP3;
	status_code child_statusP4;


    char * process_argv[] = {
		"P1","P2", "P3", "P4"}; 
	struct MemData *CommonMem;

	mem_size = MEMORY_SIZE;
	type_lang = (MT_DATA << 8);
	attr_rev = (MA_REENT<<8);

	perm = MP_OWNER_READ | MP_OWNER_WRITE;

	if(errno = _os_datmod(MEMORY_NAME,mem_size, &attr_rev, &type_lang, perm, (void **)&CommonMem, (mh_data**)&mod_head) != 0)
		{
			fprintf(stderr, "Error : Cannot create memory module\n");
		}
	else{
		 	fprintf(stderr, "Successfully created memory module\n");
		 }

   
	if (err = (_os_exec(_os_fork, 0 , 3 , process_argv[0], process_argv, envp,0,&p1_pid, 0,0) != 0))
		printf("Error1\n");	
	
	if (err = (_os_exec(_os_fork, 0 , 3 , process_argv[1], process_argv, envp,0,&p2_pid, 0,0) != 0))
		printf("Error2\n");	
	
	if (err = (_os_exec(_os_fork, 0 , 3 , process_argv[2], process_argv, envp,0,&p3_pid, 0,0) != 0))
		printf("Error3\n");	
	
	if (err = (_os_exec(_os_fork, 0 , 3 , process_argv[3], process_argv, envp,0,&p4_pid, 0,0) != 0))
		printf("Error4\n");				
	
	
	CommonMem -> PID[1] = p1_pid;
	CommonMem -> PID[2] = p2_pid;
	CommonMem -> PID[3] = p3_pid;
	CommonMem -> PID[4] = p4_pid;

    CommonMem ->MessageNumber = 222;

	/* wait for child P1 */
	if (err = (_os_wait(&p1_pid, &child_statusP1) != 0))
		printf("Error1\n");



	/* wait for child p2 */
	if (err = (_os_wait(&p2_pid, &child_statusP2) != 0))
		printf("Error2\n");


	/* wait for child  p3*/
	if (err = (_os_wait(&p3_pid, &child_statusP3) != 0))
		printf("Error3\n");


	/* wait for child  p3*/
	if (err = (_os_wait(&p4_pid, &child_statusP4) != 0))
		printf("Error4\n");


	while (1) {
		 num_ticks = 500;
		_os_sleep(&num_ticks, &dummy_sig);
		}	 					 			
}