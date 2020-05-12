#include "hrd.h"

int main()
{
	int iCSock;
	int iRet;
	struct sockaddr_in stSAddr;
	char buf[SIZE_BUF] ="Little endian";
	fd_set stRead;

	iCSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(iCSock == -1)
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
		close(iCSock);
		return 200;
	}
	stSAddr.sin_port =htons(PORT_SERVER);
	//여기까지 서버셋팅과 같음.

	getchar();
	iRet = connect(iCSock, (struct sockaddr*) &stSAddr, sizeof(stSAddr));
	if(iRet == -1)
	{
		perror("Client connect");
		close(iCSock);
		return 300;
	}

	FD_ZERO(&stRead);
	for(;;)
	{
		FD_SET(0, &stRead);
		FD_SET(iCSock,  &stRead);
		printf("Message : ");
		fflush(stdout);
		iRet = select(iCSock+1, &stRead, 0, 0, 0);
		if(-1 == iRet)
		{
			perror("Select error!");
			break;
		}

		if(0 != FD_ISSET(0,&stRead))			//key input
		{
			iRet = read(0, buf, SIZE_BUF);
			buf[iRet-1] = 0;
			write(iCSock, buf, iRet);

			if(0 == strcmp(MSG_END,buf))
			{
				break;
			}

		}
		if( 0 != FD_ISSET(iCSock, &stRead))    //client input
		{
			iRet = read(iCSock, buf, SIZE_BUF);
			if(0 == iRet)
			{
				printf("Server disconnect.\n");
				break;
			}
			printf("Server : [%s]\n", buf);
		}
	}

	close(iCSock);

	return 0;
}
