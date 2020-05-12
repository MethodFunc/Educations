#include "hrd.h"

int main()
{
	int iSSock;
	int iCSock;
	int iRet;
	struct sockaddr_in stSAddr;
	socklen_t addrlen;
	char buf[SIZE_BUF];
	fd_set stRead;

	iSSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == iSSock)
	{
		perror("Server socket");
		return 100;
	}


	memset(&stSAddr,0x00,sizeof(stSAddr));
	stSAddr.sin_family = AF_INET;
	inet_aton(IP_SERVER, &(stSAddr.sin_addr));
	if(!inet_aton(IP_SERVER, &(stSAddr.sin_addr)))
	{
		printf("IP conversion error\n");
		close(iSSock);
		return 200;
	}
	stSAddr.sin_port =htons(PORT_SERVER);
	iRet = bind(iSSock, (struct sockaddr*) &stSAddr, sizeof(stSAddr));
	if(-1 == iRet)
	{
		perror("Server Bind");
		close(iSSock);
		return 300;
	}
	printf("Server Start IP : [%s]\n",inet_ntoa(stSAddr.sin_addr));

	iRet = listen(iSSock,5);
	if(-1 == iRet)
	{
		perror("Server Listen");
		close(iSSock);
		return 400;
	}

	addrlen = sizeof(stSAddr);
	iRet = accept(iSSock,(struct sockaddr *)&stSAddr,&addrlen);
	if(-1 == iRet)
	{
		perror("Server accept");
		close(iSSock);
		return 500;

	}

	printf("Client IP : [%s]\n",inet_ntoa(stSAddr.sin_addr));
	iCSock = iRet;

	FD_ZERO(&stRead);
	for(;;)
	{
		FD_SET(0,&stRead);			//key input
		FD_SET(iCSock, &stRead);	//client input

		iRet = select(iCSock+1, &stRead, 0, 0, 0);
		if(-1 == iRet)
		{
			perror("Select error");
			break;
		}
		if(0 != FD_ISSET(0,&stRead))	//key Event
		{
			iRet = read(0, buf, SIZE_BUF);
			buf[iRet-1] = 0;
			write(iCSock, buf, iRet);
			if(0 == strcmp(MSG_END, buf))
			{
				break;
			}
		}                                     
		if(0 != FD_ISSET(iCSock, &stRead))	//client Event : message receive
		{
			iRet = read(iCSock, buf, SIZE_BUF);
			if(0 == iRet)
			{
				printf("Client disconnect.\n");
				break;
			}
			printf("Client : [%s]\n", buf);
		}
	}	

	close(iCSock);
	close(iSSock);

	return 0;
}
