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


static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

static ssize_t 	my_read(int fd,char *ptr)
{
	if (read_cnt <= 0)
	{
		again:
			if ((read_cnt = read(fd,read_buf,sizeof(read_buf))) < 0)
			{
				if (errno == EINTER)
				{
					goto again;
				}
				return(-1);
			}
			else if (read_cnt == 0)
			{
				return(0);
			}
			read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_cnt++;
	return(1);
}

ssize_t readline(int fd,vod *vptr,size_t maxlen)
{
	ssize_t n,rc;
	char c,*ptr;
	ptr = vptr;
	for (n = 1;n < maxlen;n++)
	{
		if ((rc = my_read(fd,&c)) == 1)
		{
			*ptr++ = c;
			if (c == '\n')
			{
				break;
			}
		}
		else if (rc == 0)
		{
			*ptr = 0;
			return(n -1);
		}
		else 
		{
			return(-1);
		}
	}
	*ptr = 0;
	return(0);
}




ssize_t readlinebuf(void **vptrptr)
{
	if (read_cnt)
	{
		*vptrptr = read_ptr;
	}
	return(read_cnt);
}


