#include <WinSock2.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include "hexaview.h"
#pragma comment(lib,"ws2_32")

typedef unsigned int ui;
typedef unsigned char uc;
typedef unsigned short dword;

int main()
{
	int efp;
	int iRet;
	IMAGE_DOS_HEADER *IDH;						//버퍼
	IMAGE_NT_HEADERS32 *INH;
	
	efp = open("a.exe", O_BINARY | O_RDONLY);
	if (efp < 0)
	{
		printf("파일을 열 수 없습니다.\n");
		return 100;
	}

	IDH = malloc(sizeof(IMAGE_DOS_HEADER));
	
	if (IDH == 0)
	{
		printf("메모리가 부족합니다.\n");
		close(efp);
		return 200;
	}

	iRet = read(efp, IDH, sizeof(IMAGE_DOS_HEADER));

	if (iRet != sizeof(IMAGE_DOS_HEADER))
	{
		printf("헤더를 읽을 수 없습니다.\n");
		close(efp);
		free(IDH);
		return 300;
	}

	if ( 0x5A4D != IDH->e_magic)
	{
		printf("DOS 파일이 아닙니다.\n");
		close(efp);
		free(IDH);
		return 400;
	}
	hexaview(IDH, sizeof(IMAGE_DOS_HEADER));
	printf("\n");
	printf("--------  Image   DOS	 Info  --------\n");
	printf("Magic Number         : %c%c\n", *((char *)IDH + 0), *((char *)IDH + 1));
	printf("Magic Number Word    : %04X\n", ntohs(IDH->e_magic));
	printf("cblp                 : %04X\n", ntohs(IDH->e_cblp));
	printf("cp                   : %04X\n", ntohs(IDH->e_cp));
	printf("crlc                 : %04X\n", IDH->e_crlc);
	printf("cparhdr              : %04X\n", ntohs(IDH->e_cparhdr));
	printf("minalloc             : %04X\n", IDH->e_minalloc);
	printf("maxalloc             : %04X\n", IDH->e_maxalloc);
	printf("ss                   : %04X\n", IDH->e_ss);
	printf("sp                   : %04X\n", IDH->e_sp);
	printf("csum                 : %04X\n", IDH->e_csum);
	printf("ip                   : %04X\n", IDH->e_ip);
	printf("cs                   : %04X\n", IDH->e_cs);
	printf("lfarlc               : %04X\n", ntohs(IDH->e_lfarlc));
	printf("ovno                 : %04X\n", IDH->e_ovno);
	printf("oemid                : %04X\n", IDH->e_oemid);
	printf("oeminfo              : %04X\n", IDH->e_oeminfo);
	printf("lfanew               : %08X\n", ntohl(IDH->e_lfanew));
	printf("--------------------------------------\n");
	putchar('\n');
	lseek(efp, IDH->e_lfanew, SEEK_SET);

	

	free(IDH);

	INH = malloc(sizeof(IMAGE_NT_HEADERS32));
	
	if (INH == 0)
	{
		printf("메모리가 부족합니다.\n");
		close(efp);
		return 200;
	}

	iRet = read(efp, INH, sizeof(IMAGE_NT_HEADERS32));

	if (iRet != sizeof(IMAGE_NT_HEADERS32))
	{
		printf("헤더를 읽을 수 없습니다.\n");
		close(efp);
		free(INH);
		return 301;
	}
	hexaview(INH, sizeof(IMAGE_NT_HEADERS32));
	printf("\n");

	printf("--------  Image   P E  Info  ---------\n");
	printf("Magic Number         : %c%c\n", *((char *)INH + 0), *((char *)INH + 1));
	printf("Magic Number Word    : %X%X\n", *((char *)INH + 0), *((char *)INH + 1));
	printf("Magic Number Word    : %08X\n", ntohl(INH->Signature));
	printf("--------  Image File Header  ---------\n");
	printf("이 파일은 %s 실행 파일입니다.\n", 0x014c == INH->FileHeader.Machine ? "32bit" : "64bit");
	printf("Machine              : %04X\n", ntohs(INH->FileHeader.Machine));
	printf("NumberOfSections     : %04X\n", ntohs(INH->FileHeader.NumberOfSections));
	printf("TimeDateStamp        : %08X\n", ntohl(INH->FileHeader.TimeDateStamp));
	printf("PointerToSymbolTable : %08X\n", INH->FileHeader.PointerToSymbolTable);
	printf("NumberOfSymbols      : %08X\n", INH->FileHeader.NumberOfSymbols);
	printf("SizeOfOptionalHeader : %04X\n", INH->FileHeader.SizeOfOptionalHeader);
	printf("Characteristics      : %04X\n", INH->FileHeader.Characteristics);

	free(INH);
	close(efp);



	return 0;
}