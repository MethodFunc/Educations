#include "layer3.h"

void L3_TCP(const void *vpData, struct ip* stpIPHdr)
{
	struct tcphdr *stpTHdr;

	stpTHdr = (struct tcphdr *)vpData;
	PSeudoHead			*stpPHdr;	
	unsigned int		uiTcpSegLen;

	printf("==== Layer 3 : TCP Analyzer ================================================\n");
	printf("Seq             Number : [%10u]\n", ntohl(stpTHdr -> th_seq));
	printf("Ack             Number : [%10u]\n", ntohl(stpTHdr -> th_ack));
	printf("TCP Header Size        :           [%2d] ", (stpTHdr -> th_off)*4);
	printf("     Window Size : [%d] bytes\n", ntohs(stpTHdr -> th_win));
	//	stpTHdr->th_sum	= 0;
	uiTcpSegLen = ntohs(stpIPHdr->ip_len)-(stpIPHdr->ip_hl)*4;				//ip 전체길이에서 IP Header 크기를 제거를 하면 TCP 전체의 크기를 구할 수 있다.
	stpPHdr					= malloc(sizeof(PSeudoHead)+uiTcpSegLen);		//구조체의 크기와 TCP 전체의 크기의 메모리를 할당 받아라 (쓰레기 값으로 채워져있다)
	stpPHdr->saddr			= stpIPHdr->ip_src;
	//Sedo Header 1.
	stpPHdr->daddr			= stpIPHdr->ip_dst;
	//Sedo Header 2.
	stpPHdr->protocol		= stpIPHdr->ip_p;
	stpPHdr->length			= htons(uiTcpSegLen);
	stpPHdr->zero			= 0;
	// sedo header 를 채워준다. 나머지는 쓰레기값.
	memcpy(stpPHdr+1, stpTHdr, uiTcpSegLen);
	//sedo header 바로 뒷 주소가 stpPHdr + 1 이다 그 주소에 TCP Header와 TCP DATA를 채운다
	((struct tcphdr *)(stpPHdr+1))->th_sum	= 0;
	//패킷에 안에있던 체크섬 값을 0으로 저장한다.
	//28~40 ;; 30~36 앞부분 38~40 뒷부분

	printf("Checksum value         :           [0x%04X] ",ntohs(L3_Checksum(stpPHdr, sizeof(PSeudoHead)+uiTcpSegLen)));
	printf("[%s]", (stpTHdr -> th_sum == L3_Checksum(stpPHdr, sizeof(PSeudoHead)+uiTcpSegLen))? "OK" : "Fail");

	free(stpPHdr);
	printf("    Urgent Pointer : [%d]\n", ntohs(stpTHdr -> th_urp));
	printf("Flags           [0x%02X] : ", stpTHdr -> th_flags);
	printf("FIN[%s] ", ((0==(stpTHdr -> th_flags&TH_FIN)) ? "NO" : "YES"));
	printf("SYN[%s] ", ((0==(stpTHdr -> th_flags&TH_SYN)) ? "NO" : "YES"));
	printf("RST[%s] ", ((0==(stpTHdr -> th_flags&TH_RST)) ? "NO" : "YES"));
	printf("PUSH[%s] ", ((0==(stpTHdr -> th_flags&TH_PUSH)) ? "NO" : "YES"));
	printf("ACK[%s] ", ((0==(stpTHdr -> th_flags&TH_ACK)) ? "NO" : "YES"));
	printf("URG[%s]\n", ((0==(stpTHdr -> th_flags&TH_URG)) ? "NO" : "YES"));
	
	printf("============================================================================\n");

	return ;
}

unsigned short L3_Checksum(void *vpData, int iLen)
{

	int iSum = 0;
	unsigned short usTemp = 0;

	while (iLen > 1)
	{
		iSum = iSum + *((unsigned short*)vpData);
		vpData = (unsigned short*)vpData + 1;
		iLen = iLen - 2;
	}

	if (iLen == 1)
	{
		*((unsigned char *)(&usTemp)) = *((u_char *)vpData) ;
		iSum = iSum + usTemp;
	}

	iSum = (iSum >> 16) + (iSum & 0xffff);
	iSum = (iSum >> 16) + iSum;

	return (unsigned short)(~iSum);
}

