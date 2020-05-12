#include "LoadSave.h"

BLink* FileLoad(BLink* Head, ui* uipRecord)
{

	int iFileDB = FileOpen();
	char cBuf;
	ui uiCnt;
	BLink* Temp;
	if(-1 == iFileDB)
	{
		printf("Data not Load\n");
		return Head;
	}

	for(uiCnt = 0; SIZE_MAGIC_NUMBER > uiCnt  ;++uiCnt)
	{
		read(iFileDB, &cBuf,1);
		if('*' != cBuf)
		{
			break;
		}

	}

	if(SIZE_MAGIC_NUMBER > uiCnt)
	{
		printf("Load Error : Magic Number\n");
		return Head;
	}

	LinkFree(Head);
	Head = 0;

	read(iFileDB, uipRecord, 4);

	for(uiCnt = 0 ; *uipRecord > uiCnt ; ++uiCnt)
	{
		Temp = malloc(sizeof(BLink));
		read(iFileDB, Temp, sizeof(BT));
		read(iFileDB, &cBuf, 1);			// | 읽어들이기
		Temp->next = 0;

		Head = LinkIns(Head, Temp);
	}

	return Head;
}

void FileSave(BLink* Head, ui uiRecord)
{
	int iFileDB = FileOpen();
	char cSep = '|';
	if(-1 == iFileDB)
	{
		printf("Data not Saved\n");
		return;
	}

	lseek(iFileDB, SIZE_MAGIC_NUMBER, SEEK_SET);
	write(iFileDB, &uiRecord, sizeof(uiRecord));
	while(0 != Head)
	{
		write(iFileDB, &(Head->data), sizeof(BT));
		write(iFileDB, &cSep, 1);
		Head = Head -> next;
	}
	close(iFileDB);
	return;
}
