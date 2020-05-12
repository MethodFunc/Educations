#include "main.h"

int main()
{
	int iRet;
	char caCmdLine[SIZE_CMD_LINE];
	BLink* Head	= 0;
	ui uiRecord = 0;

	Head = FileLoad(Head, &uiRecord);
	for(;;)
	{
		Menu();
		iRet = read(0, caCmdLine, SIZE_CMD_LINE);
		fflush(stdin);
		if(-1 == iRet)
		{
			perror("CMD Line Input");
			continue;
		}
		if('9' == caCmdLine[0])
		{
			write (1, "\033[1;1H\033[2J", 10); 
			printf("Program has ended.\n");
			break;
		}

		switch(caCmdLine[0])
		{
			case '1':
				Head = LinkIns(Head, LinkNew());
				++uiRecord;
				continue;
			case '2':
				LinkPrint(Head);
				getchar();
				continue;
			case '3':
				FileSave(Head, uiRecord);
				printf("Save Complete\n");
				getchar();
				continue;
			case '4':
				Head = FileLoad(Head, &uiRecord);
				printf("Load Complete\n");
				getchar();
				continue;
			case '5':
				BookSearch(Head);
				continue;
			case '9':
				break;
			default:
				printf("Wrong Selcet Number!\n");
				getchar();
				continue;

		}
		break;
	}
	FileSave(Head, uiRecord);
	LinkFree(Head);
	return 0;
}

void Menu()
{
	write (1, "\033[1;1H\033[2J", 10);		//1. stdout
	printf("=============================\n");
	printf("=   Book Managment Program  =\n");
	printf("-----------------------------\n");
	printf("== 1. Insert               ==\n");
	printf("== 2. List                 ==\n");
	printf("== 3. Save                 ==\n");
	printf("== 4. Load                 ==\n");
	printf("== 9. Quit                 ==\n");
	printf("=============================\n");
}




