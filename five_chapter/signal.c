#include "unp.h"

typedef (*signal(int signo,void (*func)(int)))(int)

Sigfunc *signal(int signo,Sigfunc *func)
{
	struct sigaction act,oact;
	act.sa_handler = func;
	sigempty(&act.sa_mask);
	act.sa_flag = 0;
#ifdef SA_INTERRUPT
	act.sa_flag |= SA_INTERRUPT;
#endif 
	else
	{
#ifdef SA_RESTART
	act.sa_flag |= SA_RESTART;
#endif 
	}
	if (sigaction(signo,&act,&oact) < 0)
	{
		return(SIG_ERR);
	}
	return(oact.sa_handler);
}


void sig_child(int signo)
{
	pid_t pid;
	int stat;
	pid = wait(&stat);
	printf("child %d terminated\n",pid);
	return;
}












