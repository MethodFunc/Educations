#ifndef __LAYER3_H__
#define __LAYER3_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

typedef struct
{
	struct in_addr saddr;
	struct in_addr daddr;
	unsigned char zero;
	unsigned char protocol;
	unsigned short length;
}__attribute__((packed)) PSeudoHead;

void L3_TCP(const void *, struct ip*);
unsigned short L3_Checksum(void *, int);

#endif    //__LAYER3_H__
