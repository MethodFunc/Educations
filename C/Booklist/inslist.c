#include "inslist.h"

void LinkPrint(BLink* Head)
{
	while(0 != Head)
	{
		printf("===================================\n");
		printf("제  목: [%s]\n",Head->data.book);
		printf("저  자: [%s]\n",Head->data.author);
		printf("출판사: [%s]\n",Head->data.publisher);
		printf("가  격: [%s]\n",Head->data.price);
		printf("발행일: [%s]\n",Head->data.year);
		Head = Head->next;
	}
	printf("===================================\n");
}


BLink* LinkNew()
{
	BLink* New = malloc(sizeof(BLink));
	int iRet;

	if(0 == New)
	{
		return 0;
	}

	printf("제  목 : ");
	fflush(stdout);
	iRet = read(0, New->data.book, LEN_NAME);
	New->data.book[iRet-1] = 0;

	printf("저  자 : ");
	fflush(stdout);
	iRet = read(0, New->data.author, LEN_AUTH);
	New->data.author[iRet-1] = 0;

	printf("출판사 : ");
	fflush(stdout);
	iRet = read(0, New->data.publisher, LEN_PUBL);
	New->data.publisher[iRet-1] = 0;

	printf("가  격 : ");
	fflush(stdout);
	iRet = read(0, New->data.price, LEN_PRIC);
	New->data.price[iRet-1] = 0;

	printf("발행일 : ");
	fflush(stdout);
	iRet = read(0, New->data.year, LEN_YEAR);
	New->data.year[iRet-1] = 0;

	New->next = 0;
}

BLink* LinkIns(BLink* Head, BLink* New)
{
	BLink* Current;
	BLink* Prev;

	Current = Head;
	Prev = Head;
	while (0 != Current)
	{
		if (0 > strcmp(New->data.book, Current->data.book))		//역순으로 정렬할려는 경우는 > 부호는 <로 바꿔주면 된다.
		{
			break;
		}
		Prev = Current;
		Current = Current->next;
	}

	if (Head == Current)
	{
		New -> next = Head;
		Head = New;
	}
	else
	{
		New->next = Current;
		Prev->next = New;
	}

	return Head;
}
