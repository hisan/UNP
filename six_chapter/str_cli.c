#include "unp.h"

void str_cli(FILE *fp,int sockfd)
{
	int maxfdp1,stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;
	stdineof = 0;
	FD_ZERO(&set);
	
	for (;;)
	{
		if (stdineof == 0)
		{
			FD_SET(fileno(fp),&rset);
		}
		
		FD_SET(sockfd,&rset);
		maxfdp1 = max(fileno(fp),sockfd) + 1;
		select(maxfdp1,&rset,NULL,NULL,NULL);//maxfdp1为什么是最大描述符+1？或许是为了内核处理时找到循环遍历描述符的跳出条件吧！
		
		if (FD_ISSET(sockfd,&rset)) 
		{
			if ( (n = read(sockfd,buf,MAXLINE)) == 0)
			{
				if (stdineof == 1)
				{
					return;
				}
				else 
				{
					err_quit("str_cli:server terminated prematually");
				}
			}
			
			write(fileno(stdout),buf,n);
		}
		
		if (FD_ISSET(fileno(fp),&rset))
		{
			if ( (n = read(fileno(fp),buf,MAXLINE)) == 0)
			{
				if ( (n = read(fileno(fp),buf,MAXLINE)) == 0)
				{
					stdinoef = 1;
					shudown(sockfd,SHUT_WR);
					FD_CLR(fileno(fp),&rset);
					continue;
				}
			}
			write(sockfd,buf,n);
		}
	}
}

