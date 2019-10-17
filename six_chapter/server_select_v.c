#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
 
typedef struct sockaddr SA;
#define socklen_t int 
#define MAXLINE 1024
#define SERV_PORT 10327
#define LISTENQ 100
#define err_quit(str) printf("%s\n",str)

int main(int argc,char **argv)
{
	int i,maxi,maxfd,listenfd,connfd,sockfd;
	int nready,client[FD_SETSIZE];
	ssize_t n;
	fd_set rset,allset;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd,(struct sockaddr *)(&servaddr),sizeof(servaddr));
	
	listen(listenfd,LISTENQ);
	maxfd = listenfd;
	maxi = -1;
	for (i = 0 ;i < FD_SETSIZE;i++)
	{
		client[i] = -1;
	}
	
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);
	
	for (;;)
	{
		rset = allset;
		nready = select(maxfd+1,&rset,NULL,NULL,NULL);//成功返回的话，返回值是读写异常三个描述符集中的已准备好进行I/O的文件描述符的总数。
		
		if (FD_ISSET(listenfd,&rset))
		{
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd,(SA*)&cliaddr,&clilen);
			
			for ( i = 0; i < FD_SETSIZE;i++)
			{
				if (client[i] < 0)
				{//判断还有哪个可用
					client[i] = connfd;
					break;
				}
			}
			
			if (i == FD_SETSIZE)
			{
				err_quit("too many clients");
			}
			
			FD_SET(connfd,&allset);
			
			if (connfd > maxfd)
			{
				maxfd = connfd;
			}
			
			if (i > maxi)
			{
				maxi = i;
			}
			
			if (--nready <= 0)
			{
				continue;
			}
		}
		
		for (i = 0 ;i <= maxi;i++)
		{
			if ( (sockfd = client[i]) < 0)
			{//获取已经建立连接的套接字
				continue;
			}
			
			if (FD_ISSET(sockfd,&rset)) 
			{//对已准备好进行I/O操作的的套接字进行操作
				if ( (n = read(sockfd,buf,MAXLINE)) == 0)
				{
					close(sockfd);
					FD_CLR(sockfd,&allset);
					client[i] = -1;
				}
				else 
				{
					write(sockfd,buf,n);
				}
				
				if (--nready <= 0)
				{
					break;
				}
			}
		}
	}	
}

