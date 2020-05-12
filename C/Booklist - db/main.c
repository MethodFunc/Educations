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
					printf("���̵� �Ǵ� ��й�ȣ�� 3�� �̻� Ʋ�Ƚ��ϴ�.\n");
					printf("���α׷��� �����մϴ�.\n");
					return 50;
				}

				ids = admin_server(ids);
				if (1 == ids->stat)
				{
					printf("������ �α��ο� �����ϼ̽��ϴ�.\n");
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
			printf("�л� �α��� â�Դϴ�.\n");
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
