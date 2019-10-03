#include	<string.h>
#include 	<sys/socket.h>
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include 	<signal.h>

		   
int main(int argc,char *argv[])
{
	int listenfd,connfd;
	int readcnt = 0;
	char *buff = "this is server>\n";
	
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(87);

	inet_aton(argv[1], (struct in_addr *)(&servaddr.sin_addr.s_addr));
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bind(listenfd,(const struct sockaddr *)&servaddr,sizeof(struct sockaddr));
	listen(listenfd,1024);
	
	sigset_t sigmask;
	sigemptyset(&sigmask);
	sigfillset(&sigmask);
	sigprocmask(SIG_SETMASK,&sigmask,NULL);
	
	for (;;)
	{
		connfd = accept(listenfd,(struct sockaddr *)NULL,NULL);
		write(connfd,buff,strlen(buff));
	}
	
	exit(0);
}