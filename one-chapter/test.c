#include <stdio.h>
#include <unistd.h>

int main()
{
	int n = 6;
	if (n)
	{
		n++,printf("%d\n",n);//C语言逗号表达式
	}
	exit(0);
}

//client
int sockfd = socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in servaddr;
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(13);

if (1 != inet_pton(AF_INET,argv[1],&servaddr.sin_addr))
{
	printf("transe addr error");
}

if (0 != connect(sockfd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr)))
{
	printf("connect error");
}
//read write

//server
int connfd;
struct sockaddr_in servaddr;
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(13);
servaddr.sin_addr = htonl(INADDR_ANY);



int listenfd = socket(AF_INET,SOCK_STREAM,0);
if (0 != bind(listenfd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr)))
{
	printf("bind sockfd error");
}

if (0 != listen(listenfd,1024))
{
	printf("listen func error");
}


for (;;)
{
	connfd= accept(listenfd,(struct sockaddr *)NULL,NULL);
	//利用建立起来的描述符进行内容的传输
}













