#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <string.h>		//strcmp...
#include <stdlib.h>		//malloc
#include <errno.h>		//number of last error ; perror
#include "LoadSave.h"
#include "openf.h"
#include "inslist.h"
#include "LoadSave.h"
#include "search.c"

#define FILE_NAME		 "BOOK.DBF"
#define LEN_NAME			 30
#define LEN_AUTH			 15
#define LEN_PUBL			 15
#define LEN_PRIC			 15
#define LEN_YEAR			 15
#define SIZE_CMD_LINE		 10
#define SIZE_MAGIC_NUMBER	 30

#pragma pack(push, 1)
typedef unsigned int ui;

struct booktype  {
	//책제목
	char book[LEN_NAME];
	//책 저자
	char author[LEN_AUTH]; 
	//출판사
	char publisher[LEN_PUBL]; 
	//가격
	char price[LEN_PRIC]; 
	//출시년도
	char year[LEN_YEAR];
};
#pragma pack(pop)

typedef struct booktype BT;

typedef struct _BLink
{
	BT data;
	struct _BLink *next;
}BLink;

#pragma pack(push, 1)
typedef struct _FileHeader
{
	char mnum[SIZE_MAGIC_NUMBER];			//Magic Number;
	ui record;				//Number of Record
}FileHeader;
#pragma pack(pop)

void Menu();
int FileOpen();
void LinkFree(BLink* );
void LinkPrint(BLink* );
BLink* LinkNew();
BLink* LinkIns(BLink* ,BLink *);
void FileSave(BLink*, ui);
BLink* FileLoad(BLink*, ui*);
#endif //__MAIN_H__
