#ifndef __LAYER2_H__
#define __LAYER2_H__

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>

typedef struct
{
	unsigned int uiL3PNumber;
	char * cpL3PName;
}L3_PName;

void L2_IP(const void *);
char *L3_NameSearch(unsigned int);
unsigned short L2_IPChecksum(void*, unsigned int);

#endif     //__LAYER2_H__
