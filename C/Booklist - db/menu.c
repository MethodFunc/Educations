#include "main.h"

enum main_select { TLIST = '1' ,TADD ,TDEL, TSCH, EXIT };

void main_menu()
{

	printf("[1]관리자  [2]교원  [3]학생  [4]종료\n");
}

void admin_menu()
{
	int iCnum;
	unsigned int uiRecord = 0;
	Teach* Head = 0;

	for (;;)
	{
		
		printf("[1]교원목록 [2]교원등록  [3]교원삭제  [4]교원찾기  [5]종료\n");
		iCnum = _getch();

		switch (iCnum)
		{
		case TLIST:
			TeachPrint(Head);
			continue;

		case TADD:
			Head = InsTeach(Head, NewTeach());
			++uiRecord;
			continue;
			
		case TDEL:
			TeachDel(Head);
			continue;

		case TSCH:
			TeachSearch(Head);
			continue;

		case EXIT:
			break;
			
		default:
			system("cls");
			continue;
		}
		break;
	}
	LinkFree(Head);
}