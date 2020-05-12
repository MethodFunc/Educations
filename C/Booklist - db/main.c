/* 2019. 07 . 06  Login linked start*/

#include "main.h"

enum main_select { ADMIN = '1', TEACHER, STUDENT, EXIT };

int main()
{
	Admin* ids = malloc(sizeof(Admin));
	Teach* Head = malloc(sizeof(Teach));;
	int iCnum;
	int i = 0;

	for (;;)
	{
		main_menu();
		iCnum = _getch();
		switch (iCnum)
		{
		case ADMIN:
			
			for (i = 0; i < 4; i++)
			{
				if (i == 3)
				{
					system("cls");
					printf("아이디 또는 비밀번호를 3번 이상 틀렸습니다.\n");
					printf("프로그램을 종료합니다.\n");
					return 50;
				}

				ids = admin_server(ids);
				if (1 == ids->stat)
				{
					printf("관리자 로그인에 성공하셨습니다.\n");
					Sleep(1000);
					system("cls");
					
					for (;;)
					{
						admin_menu();
						break;
					}
					break;
				}
			}
			continue;
			
		case TEACHER:
			teach_server(Head, ids);
			continue;
		case STUDENT:
			printf("학생 로그인 창입니다.\n");
			continue;
		case EXIT:
			break;

		default:
			system("cls");
			continue;
			}
			break;
		}

	free(ids);
	return 0;
}
