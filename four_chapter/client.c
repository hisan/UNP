#include	<stdio.h>
#include 	<sys/socket.h>
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */

int main(int argc ,char **argv)
{
	int sockfd;
	char buff[1024] = {0};
	struct sockaddr_in addr;
	
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(87);
	inet_pton(AF_INET,argv[1], &addr.sin_addr);
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	connect(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr));
	read(sockfd,buff,sizeof(buff));
	printf("%s\n",buff);
}