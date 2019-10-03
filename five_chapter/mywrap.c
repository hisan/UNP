#include "mywrap.h"
#include <sys/socket.h>
#include <netinet/in.h>

#define	SA	struct sockaddr
#define INPUTS(s)	printf("%s,%s:%d\n",s,__func__,__LINE__);

int m_socket(int family,int type,int proto)
{
	int fd = socket(family,type,proto);
	if (fd < 0)
	{
		INPUTS("socket error");
	}
	return fd;
}

int m_bind(int sockfd,SA *psockaddr,int len)
{
	int ret = 0;
	ret = bind(sockfd,psockaddr,len);
	if (ret == -1)
	{
		INPUTS("bind error");
	}
	return ret;
}

int m_listen(int sockfd,int queuelen)
{
	if(-1 == listen(sockfd,queuelen))
	{
		INPUTS("listen error");
	}
	return 0;
}