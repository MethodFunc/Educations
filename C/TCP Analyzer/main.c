#include "main.h"

static unsigned int uiStop;    //항상 0을 가지고있다..... 전역변수

static void MainStop(int iArg)
{
	printf("Break..........\n");
	uiStop = 1;
}

int main(int iArg, char *cpaArg[])
{
	char errbuf[PCAP_ERRBUF_SIZE];
	char *cpNICname;
	pcap_t *stpHandle;
	const u_char *ucpData;
	struct pcap_pkthdr stPInfo;		//패킷의 정보를 가지고 있다.[패킷 크기, 캡쳐시간 등]
	unsigned short usPort;

	if(2 == iArg)
	{
		usPort = atoi(cpaArg[1]);
		if(0 > usPort || 65535 < usPort)
		{
			usPort = PORT_DEFAULT;
		}
	}
	else
	{
		usPort = PORT_DEFAULT;
	}

	signal(SIGINT, MainStop);		//ctrl + c 를 누를때 마다 mainstop을 실행한다.

	cpNICname = pcap_lookupdev(errbuf);
	if(NULL == cpNICname)
	{
		printf("pcap_lookupdev : [%s]\n",errbuf);
		return 100;
	}
	printf("[%s]\n",cpNICname);

	stpHandle = pcap_open_live(cpNICname, 1500, 1, 0, errbuf);
	if(NULL == stpHandle)
	{
		printf("stpHandle : [%s]\n",errbuf);
		return 200;
	}

	for(;;)
	{
		for(;;)
		{
			ucpData = pcap_next(stpHandle, &stPInfo);
			if(NULL == ucpData)
			{
				printf("Retry capture\n");
				continue;
			}
			break;
		}
		if(1 == uiStop)
		{
			break;
		}

		if(*((unsigned short *)(ucpData + 12)) != 0x0008 )
		{
			continue;
		}

		if(IPPROTO_TCP != *(ucpData + 23))
		{
			continue;
		}
		if(htons(usPort) != (*(unsigned short *)(ucpData+ETH_HLEN + (*(ucpData+ETH_HLEN)&0x0F)*4)))
			//0x0f 는 mask 뒤에 있는 4bit만 추출해준다.(34byte) 추출
		{
			if(htons(usPort) != (*(unsigned short *)(ucpData+ETH_HLEN + (*(ucpData+ETH_HLEN)&0x0F)*4+2)))
				continue;
		}

		printf("[%d]\n", stPInfo.caplen);
		hexaview(ucpData, stPInfo.caplen);
		L1_Ethernet(ucpData);
		L2_IP(ucpData + ETH_HLEN);
		L3_TCP(ucpData + ETH_HLEN +( (*(ucpData + ETH_HLEN)) & 0x0f )*4,(struct ip*)(ucpData + ETH_HLEN));	// == ucpData + 34

		printf("\n");
		printf("\n");
//		break;



	}
	pcap_close(stpHandle);

	return 0;
}
