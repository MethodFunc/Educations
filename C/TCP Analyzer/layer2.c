#include "layer2.h"

void L2_IP(const void *vpData)
{
	struct ip *stpIHdr = (struct ip *)vpData;
	unsigned int uiCSum;

	printf("===== Layer 2 : IP ==========================================================\n");
	printf("Fragmentation Flag     :           RF [%s]", (0 == (ntohs(stpIHdr ->ip_off)&IP_RF)) ? "NO" : "YES");
	printf(" DF[%s]", (0 == (ntohs(stpIHdr ->ip_off)&IP_DF)) ? "NO" : "YES");
	printf(" MF[%s]", (0 == (ntohs(stpIHdr ->ip_off)&IP_MF)) ? "NO" : "YES");
	printf(" Offset[%d] 0x%04X\n", ntohs(stpIHdr->ip_off)&IP_OFFMASK, ntohs(stpIHdr->ip_off)&IP_OFFMASK);

	printf("IP                     :           [%s:%u] -> ", inet_ntoa(stpIHdr->ip_src), ntohs(*(unsigned short *)((char *)vpData+ stpIHdr->ip_hl * 4)));
	printf("[%s:%u]\n", inet_ntoa(stpIHdr->ip_dst), ntohs(*(unsigned short *)((char *)vpData + stpIHdr->ip_hl * 4 + 2)));
	printf("IP Version             :           [%d] ", stpIHdr->ip_v);
	printf("      Identification : [%d], 0x%04X\n", ntohs(stpIHdr->ip_id), ntohs(stpIHdr->ip_id));
	printf("IP Header Size         :           [%d]", stpIHdr->ip_hl * 4);
	printf("      Total Length : [%d] bytes\n", ntohs(stpIHdr->ip_len));
	printf("Time to live           :           [%d] ",  stpIHdr ->ip_ttl);

	uiCSum = stpIHdr->ip_sum;
	stpIHdr->ip_sum = 0;
	printf("    IP  checksum : [%04X], [%s]\n", ntohs(uiCSum),
			uiCSum == L2_IPChecksum(stpIHdr, stpIHdr->ip_hl* 4)?"OK":"Fail"
		  );


	return;
}

char *L3_NameSearch(unsigned int uiProto)
{

	unsigned int uiCnt;

	L3_PName stL3Name[] = { {IPPROTO_IP, "Dummy protocol for TCP."},
		{IPPROTO_ICMP, "Internet Control Message Protocol."},
		{IPPROTO_IGMP, "Internet Group Management Protocol. "},
		{IPPROTO_IPIP, "IPIP tunnels (older KA9Q tunnels use 94)."},
		{IPPROTO_TCP, "Transmission Control Protocol."},
		{IPPROTO_EGP, "Exterior Gateway Protocol."},
		{IPPROTO_PUP, "PUP protocol."},
		{IPPROTO_UDP, "User Datagram Protocol."},
		{IPPROTO_IDP, "XNS IDP protocol."},
		{IPPROTO_TP, "SO Transport Protocol Class 4."},
		{IPPROTO_DCCP, "Datagram Congestion Control Protocol."},
		{IPPROTO_IPV6, "IPv6 header."},
		{IPPROTO_RSVP, "Reservation Protocol."},
		{IPPROTO_GRE, "General Routing Encapsulation."},
		{IPPROTO_ESP, "encapsulating security payload."},
		{IPPROTO_AH, "authentication header."},
		{IPPROTO_MTP, "Multicast Transport Protocol."},
		{IPPROTO_BEETPH, "IP option pseudo header for BEET."},
		{IPPROTO_ENCAP, "Encapsulation Header."},
		{IPPROTO_PIM, "Protocol Independent Multicast."},
		{IPPROTO_COMP, "Compression Header Protocol."},
		{IPPROTO_SCTP, "Stream Control Transmission Protocol."},
		{IPPROTO_UDPLITE, "UDP-Lite protocol."},
		{IPPROTO_MPLS, "MPLS in IP."},
		{IPPROTO_RAW, "Raw IP packets."}
	};

	for (uiCnt = 0 ;uiCnt < sizeof(stL3Name)/sizeof(stL3Name[0]); ++uiCnt)
	{
		if(stL3Name[uiCnt].uiL3PNumber == uiProto)

		{
			break;
		}

	}

	if(stL3Name[uiCnt].uiL3PNumber != uiProto)
	{
		--uiCnt;
		return "Unknown Protocol";
	}
	else
	{
		return stL3Name[uiCnt].cpL3PName;
	}

}

unsigned short L2_IPChecksum(void* vpData, unsigned int uiLen)
{
	unsigned long ulSum ;
	for ( ulSum=0 ; uiLen>0 ; uiLen=uiLen-2 )
	{
		ulSum = ulSum + *((unsigned short *)vpData);
		vpData = (unsigned short *)vpData + 1;
	}
	ulSum = (ulSum>>16) + (ulSum&0xffff) ;
	ulSum = ulSum + (ulSum>>16) ;
	return ~ulSum;
}
