#include 	<stdio.h>
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include 	<unistd.h>

#define MAXLINE 1024
#define	SA	struct sockaddr
#define err_quit printf
#define err_sys printf

//ipv4
int main(int argc ,char **argv)
{
	int sockfd,n;
	char recvline[MAXLINE];
	struct sockaddr_in servaddr;
	
	if (argc != 2)
	{
		err_quit("usage:a.out <IPaddress>\n");
		exit(0);
	}
	
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{//创建一个套接字，并返回该套接字的文件描述符
		err_sys("socket error");
	}
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	if (inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
	{
		err_quit("inet_pton error for %s",argv[1]);
	}
	
	if (connect(sockfd,(SA*)&servaddr,sizeof(servaddr)) < 0)
	{
		err_sys("connect error");
	}
	printf("the client sockfd is %d\n",sockfd);
	int readcnt = 0;
	while ((n = read(sockfd,recvline,MAXLINE)) > 0)
	{
		readcnt++;
		recvline[n] = 0;
		if (fputs(recvline,stdout) == EOF)
		{
			err_sys("fputs error");
		}
	}
	
	if (n < 0)
	{
		err_sys("read error");
	}
	printf("cli:the read count is %d\n",readcnt);
	exit(0);
}

//ipv6
int main2(int argc,char **argv)
{
	int sockfd,n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in6 servaddr;
	
	if (argc != 2)
	{
		err_quit("usage:a.out <IP6address>\n");
		exit(0);
	}
	
	if ((sockfd = socket(AF_INET6,SOCK_STREAM,0)) < 0)
	{//创建一个套接字，并返回该套接字的文件描述符
		err_sys("socket error");
	}
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(13);
	if (inet_pton(AF_INET6,argv[1],&servaddr.sin6_addr) <= 0)
	{
		err_quit("inet_pton error for %s",argv[1]);
	}
	
	if (connect(sockfd,(SA *)&servaddr,sizeof(servaddr)) < 0)
	{
		err_sys("connect error");
	}
	
	while ((n = read(sockfd,recvline,MAXLINE)) > 0)
	{
		recvline[n] = 0;
		if (fputs(recvline,stdout) == EOF)
		{
			err_sys("fputs error");
		}
	}
	
	if (n < 0)
	{
		err_sys("read error");
	}
	
	exit(0);
}



