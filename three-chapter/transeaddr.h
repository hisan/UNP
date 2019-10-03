#ifdef __INET_TRANSE_ADDT__
#define __INET_TRANSE_ADDT__

char *sock_ntop(const struct sockaddr * sa,socklen_t salen)
{
	char portstr[8];
	static char str[128];
	
	switch(sa->family)
	{
		case AF_INET:
			struct sockaddr_in *sin = (struct sockaddr_in *)sa;
			
			if (inet_ntop(AF_INET,&sin->sin_addr,str,sizeof(str)) == NULL)
			{
				return(NULL);
			}
			
			if (ntohs(sin->sin_port) != 0)
			{
				snprintf(portstr,sizeof(portstr),":%d",ntohs(sin->sin_port));
				strcat(str,portstr);
			}
			
			break;
		case AF_INET6:
		
			break;
		default:
			break;
	}
}

ssize_t readn(int fd,void *vptr,size_t n)
{
	ssize_t nleft;
	ssize_t nread;
	char 	*ptr;
	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ((nread = read(fd,ptr,nleft)) < 0)
		{
			if (errno == EINTR)
			{
				nread = 0;
			}
			else 
			{
				return(-1);
			}
		}
		else if (nread == 0)
		{
			break;
		}
		
		nleft -= nread;
		ptr += nread;
	}
	return(n - nleft);
}

ssize_t writen(int fd,void *vptr,size_t n)
{
	ssize_t nleft;
	ssize_t nwrite;
	char 	*ptr;
	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ((nwrite = write(fd,ptr,nleft)) < 0)
		{
			if ((errno == EINTR)&&(nwrite < 0))
			{
				nwrite = 0;
			}
			else 
			{
				return(-1);
			}
		}
		
		nleft -= nwrite;
		ptr += nwrite;
	}
	return(n);
}







































#endif 