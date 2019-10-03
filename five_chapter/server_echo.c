#include "unp.h"
#define err_sys(s) printf("%s\n",s);

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
again:
	while ((n = read(sockfd,buf, MAXLINE)) > 0)
	{
		write(sockfd,buf,n);
		if (n < 0 && errno == EINTR)
		{
			goto again;
		}
		else if (n < 0)
		{
			err_sys("str_echo :read error");
		}
	}
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	
	while ((pid = waitpid(-1,&stat,WNOHANG)) > 0)//WNOHANG告诉内核，如系统中有尚未终止的子进程，这不要阻塞
		printf("child %d terminated\n",pid);
	
	//pid = wait(&stat);
	//printf("child %d terminated\n",pid);
	return;
}

int main(int argc,char **argv)
{
	int listenfd,connfd;
	int clilen;
	pid_t childpid;
	socklen_t len;
	struct sockaddr_in cliaddr,servaddr;
	
	void sig_chld(int);
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
	listen(listenfd,LISTENQ);
	signal(SIGCHLD,sig_chld);
	
	for(;;)
	{
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd,(SA *)&cliaddr,&clilen)) < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			else 
			{
				err_sys("accept error");
			}
		}
		
		if ((childpid = fork()) == 0)
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);//parent close the connect sockfd
	}
}








