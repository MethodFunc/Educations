#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "login_server.h"
#include "teacher.h"

#define ADMIN_ID "admin"
#define ADMIN_PASS "12"
#define ID_SIZE 20
#define PAWD_SIZE 20
#define NAME_SIZE 10

#pragma pack(push,1 )

typedef struct
{
	char id[ID_SIZE];
	char pass[PAWD_SIZE];
	char name[NAME_SIZE];
	int stat;
}Admin;

typedef struct _teach
{
	Admin data;
	struct _teach* next;
}Teach;

#pragma pack(push, pop)

Admin login_server(char, char);
Admin* admin_server(Admin*);
Teach* NewTeach();
Teach* InsTeach(Teach*, Teach*);
void TeachPrint(Teach*);
void TeachSearch(Teach*);
Teach* TeachDel(Teach*);

#endif __MAIN_H__