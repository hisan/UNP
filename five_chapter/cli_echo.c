#include "unp.h"
#define err_quit(s) printf("%s\n",s);

void str_cli(FILE *fp,int sockfd)
{
	char sendline[MAXLINE],recvline[MAXLINE];
	while (fgets(sendline,MAXLINE,fp) != NULL)
	{
		write(sockfd,sendline,strlen(sendline));
		if (read(sockfd,recvline,MAXLINE) == 0)
		{
			err_quit("str_cli:server terminated prematually");
		}
		fputs(recvline,stdout);
	}
}

int main(int argc,char **argv)
{
	int sockfd[5];
	int i;
	struct sockaddr_in servaddr;
	if (argc != 2)
	{
		err_quit("usgae:a.out <IpAddress>\n");
		exit(127);
	}
	for (;i < 5;i++)
	{
		sockfd[i] = socket(AF_INET,SOCK_STREAM,0);
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
		connect(sockfd[i],(SA *)&servaddr,sizeof(servaddr));
	}
	str_cli(stdin,sockfd[0]);
	
	exit(0);
}