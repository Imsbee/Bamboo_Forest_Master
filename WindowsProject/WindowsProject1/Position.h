#pragma once
#include <stdio.h>
#include <windows.h>

// 똥
typedef struct
{
	int x;
	int y;
	BOOL state;	// 적의 상태(TURE or FALSE)
}Enemy;

// 플레이어
typedef struct
{
	int x;
}User;

// 지정된 위치로 커서를 이동 시켜주는 함수
void gotoxy(int x, int y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}