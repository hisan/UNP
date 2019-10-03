#include <stdio.h>
//int m_socket(int family,int type,int proto)
int main()
{
	int fd = m_socket(AF_INET,SOCK_STREAM,0);
	printf("%d\n",fd);
}