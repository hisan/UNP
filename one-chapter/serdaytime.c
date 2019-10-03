#include "unp.h"
#include <time.h>
#define err_quit printf

int main(int argc,char **argv)
{
	int listenfd,connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
    if ((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		err_quit("listen error\n");
	}
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//当服务器主机有多个网口的时候，将服务器地址设置为INADDR_ANY，服务器进程就可以在任意网络接口上接受客户程序
	servaddr.sin_port = htons(9999);
	
	if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr)) != 0)
	{
		err_quit("bind error\n");
	}
	
	listen(listenfd,LISTENQ);
	//LISTENQ = 1024 ，指定系统内核允许在这个监听描述符上排队的最大客户连接数
	for (;;)
	{
		int bytecnt = 0;
		connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
		printf("the server connfd sockfd is %d\n",connfd);
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));//sprintf不能检查换缓冲区是否溢出
		while (bytecnt < sizeof(buff))
		{
			write(connfd,&buff[bytecnt],sizeof(char));
			bytecnt++;
		}
		close(connfd);
	}
	
}