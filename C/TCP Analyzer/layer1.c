#include "layer1.h"

void L1_Ethernet(const void *vpData)
{

	unsigned int iCount;
	printf("MAC                    :      [");
	for(iCount = 0; ETH_ALEN > iCount ; ++iCount)
	{
		printf("%02X:", ((struct ethhdr *)vpData)->h_source[iCount]);
	}
	printf("\b] ->  [");
	for(iCount = 0; ETH_ALEN > iCount ; ++iCount)
	{
		printf("%02X:", ((struct ethhdr *)vpData)->h_dest[iCount]);
	}
	printf("\b]\n");
	
	return ;
}

