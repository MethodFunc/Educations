#include "hexaview.h"

void hexaview(const void *vpData, unsigned int uiLen)
{
	unsigned int uiCnt;
	unsigned int uiLine;
	printf("==============================================================================\n");
	printf(" Address                         Hexa                              ASCII\n");
	printf("------------------------------------------------------------------------------\n");
	for (uiLine = 0; uiLine < uiLen; uiLine = uiLine + 16)
	{
		printf(" %08X  ", uiLine);
		for (uiCnt = 0; uiCnt < 16; ++uiCnt)
		{
			printf("%02X ", *((unsigned char *)vpData));
			vpData = (char *)vpData + 1;
			if (uiCnt == 7)
			{
				putchar(' ');
			}
		}
		vpData = (char *)vpData - 16;

		putchar(' ');
		for (uiCnt = 0; uiCnt < 16; ++uiCnt)
		{
			if (32 > *((unsigned char *)vpData))
			{
				putchar('.');
			}
			else if (127 < *((unsigned char *)vpData))  
			{
				putchar('.');
			}
			else
			{
				printf("%c", *((unsigned char *)vpData));
			}
			vpData = (char *)vpData + 1;
		}
		putchar('\n');
	}
	return;
}
