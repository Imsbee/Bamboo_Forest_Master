#pragma once
#include <stdio.h>
#include <windows.h>

// ��
typedef struct
{
	int x;
	int y;
	BOOL state;	// ���� ����(TURE or FALSE)
}Enemy;

// �÷��̾�
typedef struct
{
	int x;
}User;

// ������ ��ġ�� Ŀ���� �̵� �����ִ� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}