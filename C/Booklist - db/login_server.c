#include "login_server.h"

Admin login_server(char id[ID_SIZE], char pw[PAWD_SIZE])
{

	int buffer = 0;
	int i = 0;
	printf("ID : ");
	fgets(id, ID_SIZE, stdin);
	id[strlen(id) - 1] = '\0';

	printf("PASSWORD : ");
	for (i = 0; buffer != 13; i++) {
		pw[i] = _getch();
		if (pw[i] == '\0') {
			i--;
			continue;
		}
		_putch('*');
		buffer = (int)pw[i];
	}
	pw[i - 1] = '\0';
	printf("\n");

}

Admin *admin_server(Admin *admin)
{
	int stat1;
	int stat2;

	login_server(admin->id, admin->pass);

	stat1 = ((1 == strcmp(admin->id, ADMIN_ID)) || (-1 == strcmp(admin->id, ADMIN_ID)));
	stat2 = ((1 == strcmp(admin->pass, ADMIN_PASS)) || (-1 == strcmp(admin->pass, ADMIN_PASS)));

	if (1 == stat1 || 1 == stat2)
	{
		printf("아이디 또는 비밀번호가 틀렸습니다.\n");
		admin->stat = (-1 == (stat1 && stat2));
	}
	else {
		
		admin->stat = (0 == (stat1 && stat2));
	}
}

//Admin* teach_server(Admin* admin)
//{
//
//}