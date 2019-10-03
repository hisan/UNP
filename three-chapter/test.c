#include <stdio.h>

int main()
{
	int *p = (int*)malloc(sizeof(int)*100);
	printf("%d%d%d%d\n",p[0],p[1],p[2],p[3]);
	bzero(p,sizeof(int)*100);
	printf("%d%d%d%d\n",p[0],p[1],p[2],p[3]);
	free(p);
	exit(0);
}


int inet_pton(int family,const char *strptr,void *addrptr)
{//  just ipv4
	if (family == AF_INET)
	{
		struct in_addr in_val;
		if (inet_aton(strptr,&in_val))
		{
			memcpy(addrptr,&in_val,sizeof(struct in_addr));
			return(1);
		}
		return(0);
	}
	errno = EAFNOSUPPORT;
	return(-1);
}
	
const char *inet_ntop(int family,const void *addrptr,char *strptr,size_t len)
{//  just ipv4
	const u_char *p = (const u_char *)addrptr;
	
	if (family == AF_INET)
	{
		char temp[16];
		snprintf(temp,sizeof(temp),"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
		if (strlen(temp) >= len)
		{
			errno = ENOSPC;
			return(NULL);
		}
		strcpy(strptr,temp);
		return(strptr);
	}
	errno = EAFNOSUPPORT;
	return(NULL);
}

















