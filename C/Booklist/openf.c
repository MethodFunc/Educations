#include "openf.h"

int FileOpen()
{
	int iFileDB;

	for(;;)
	{
		iFileDB = open(FILE_NAME, O_RDWR);
		if(-1 == iFileDB)
		{
			if(ENOENT == errno)		//no search file or dir
			{
				FileHeader stTempHeader;
				iFileDB = open(FILE_NAME, O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

				memset(&stTempHeader, '*', 30);
				stTempHeader.record = 0;
				write( iFileDB, &stTempHeader, sizeof(FileHeader));
				//				printf("sizeof(FileHeader) : [%d]\n", sizeof(FileHeader));

				close(iFileDB);
				continue;
			}
			else
			{
				perror("open");
			}
		}
		break;
	}
	return iFileDB;
}

void LinkFree(BLink* Head)
{
	BLink* Temp;
	while(0 != Head)
	{
		Temp = Head;
		Head = Head -> next;
		free(Temp);
	}
}