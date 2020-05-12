#include "open.h"

FILE* FileOpen()
{
	FILE* iFile;
	for (;;)
	{
		iFile = fopen_s(&iFile, FILE_NAME, "ab");
		if (-1 == iFile)
		{
			printf("error \n");
			continue;
		}
		else
		{
			printf("open");
			break;
		}
	}
		
}


FILE* FileSave(Teach* Head, unsigned int uiRecord)
{
	FILE* iFile = FileOpen();
	char cSep = '|';
	if (NULL == iFile)
	{
		printf("Data not saved\n");
		return;
	}
	//_lseek(iFile, SEEK_SET);

	//fwrite(Head,sizeof(Teach), sizeof(uiRecord), iFile);
	while (0 != Head)
	{
		fread(&(Head->data), sizeof(Teach), sizeof(uiRecord), iFile);
		fwrite(&cSep, 1, 1, iFile);
		Head = Head->next;
	}
	fclose(iFile);
	return;
}

/*
Teach* FileOpen(Teach* Head, unsigned int* uipRecord)
{
	int iFile = FileOpen();
	char cBuf;
	unsigned int uiCnt;
	Teach* Temp;
	if (-1 == iFile)
	{
		printf("File not Load\n");
		return Head;
	}
	Head = 0;

	_read(iFile, uipRecord, 4);

	for (uiCnt = 0; *uipRecord > uiCnt; ++uiCnt)
	{
		Temp = malloc(sizeof(Teach));
		_read(iFile, Temp, sizeof(Admin));
		_read(iFile, &cBuf, 1);
		Temp->next = 0;

		Head = InsTeach(Head, Temp);
	}
}

*/