/* 2019. 07 . 07 Teach linked start*/

#include "teacher.h"

Teach* NewTeach()
{
	Teach* New = malloc(sizeof(Teach));				//�޸� �Ҵ�.

	if (0 == New)									//�Ҵ�� �޸𸮰� 0�̸� ����
	{
		return 0;
	}

	printf("�� ���� ID : ");
	fgets(New->data.id, ID_SIZE, stdin);
	for (int i = 0; i < ID_SIZE; ++i)
	{
		if ('\n' == New->data.id[i])
		{
			New->data.id[i] = 0;
		}

		if (-51 == New->data.id[i])			// '?'�� -51�� ������ �ݺ����� �������´�.
		{
			break;
		}
	}

	printf("��й�ȣ : ");
	fgets(New->data.pass, PAWD_SIZE, stdin);
	for (int i = 0; i < ID_SIZE; ++i)
	{
		if (New->data.pass[i] == '\n')
		{
			New->data.pass[i] = 0;
		}

		if (-51 == New->data.id[i])
		{
			break;
		}

	}

	printf("�� ���� �̸� : ");
	fgets(New->data.name, NAME_SIZE, stdin);
	for (int i = 0; i < NAME_SIZE; ++i)
	{
		if (New->data.name[i] == '\n')
		{
			New->data.name[i] = 0;
		}

		if (-51 == New->data.id[i])
		{
			break;
		}
	}

	New->next = 0;									//New -> next �� 0�� �Ҵ�.
}

Teach* InsTeach(Teach* Head, Teach* New)
{
	Teach* Current;
	Teach* Prev;

	Current = Head;
	Prev = Head;

	while (0 != Current)
	{
		if (0 > strcmp(New->data.id, Current->data.id))
		{
			break;
		}
		Prev = Current;
		Current = Current->next;
	}

	if (Head == Current)
	{
		New->next = Head;
		Head = New;
	}
	else
	{
		New->next = Current;
		Prev->next = New;
	}
	return Head;
}

void TeachPrint(Teach* Head)
{
	int i = 1;

	printf("���� ����\n");
	while (0 != Head)
	{
		printf("���� : [%d] ", i);
		printf("���� �̸� : %s ", Head->data.name);
		printf("ID : %s\n", Head->data.id);
		++i;
		Head = Head->next;
	}
}

Teach* TeachDel(Teach* Head)
{
	if (NULL == Head)
	{
		return 0;
	}

	Teach* Del = malloc(sizeof(Teach));
	Teach* Temp = Head;
	Teach* Prev = Head;
	TeachPrint(Head);

	printf("������ ���� �̸� : ");
	fgets(Del->data.name, NAME_SIZE, stdin);
		for (int i = 0; i < NAME_SIZE; ++i)
	{
		if (Del->data.name[i] == '\n')
		{
			Del->data.name[i] = 0;
		}

		if (-51 == Del->data.name[i])
		{
			break;
		}

	}
	if (0 == (strcmp(Del->data.name, Head->data.name)))
	{
		Head = Head->next;							//ù��°�� �����
		free(Temp);
		return Head;
	}

	while (0 != Head)
	{

		if (0 == (strcmp(Del->data.name, Head->data.name)))
		{
			if (Temp == Head)
			{
				break;
			}
		}

			Prev = Head;
			Temp = Temp->next;
			Head = Head->next;
	}

	if (Prev->next != NULL)
	{
		Prev->next = Head->next;
		Head = Prev;
	}

	if (Prev->next == NULL)
	{
		Prev->next = 0;
	}
	free(Temp);
	return Head;

}


void TeachSearch(Teach* Head)
{
	Teach* Ser = malloc(sizeof(Teach));

	printf("ã�� ���� �̸� : ");
	fgets(Ser->data.name, NAME_SIZE, stdin);
	for (int i = 0; i < NAME_SIZE; ++i)
	{
		if (Ser->data.name[i] == '\n')
		{
			Ser->data.name[i] = 0;
		}

		if (-51 == Ser->data.name[i])
		{
			break;
		}

	}
	while (0 != Head)
	{
		if (0 == (strcmp(Ser->data.name, Head->data.name)))
		{
			printf("���� ���̵� : %s ", Head->data.id);
			printf("���� �̸� : %s\n", Head->data.name);
			Head = Head->next;
		}
		else
		{
			Head = Head->next;
		}
	}
}

int count(Teach* Head)
{
	if (NULL == Head)
	{
		return 0;
	}
	else
	{
		return (1 + count(Head->next));
	}
}
void LinkFree(Teach* Head)
{
	Teach* Temp;
	while (0 != Head)
	{
		Temp = Head;
		Head = Head->next;
		free(Temp);
	}
}