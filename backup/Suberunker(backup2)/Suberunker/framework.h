// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <windowsx.h>
#include <D2DBaseTypes.h>

// 윈도우 크기
#define WINSIZEX 1280
#define WINSIZEY 760

BOOL isStart;
BOOL KeyBuffer[256];
RECT rtBox1;	// 플레이어의 RECT
RECT startBtn = { WINSIZEX / 2 - 150, WINSIZEY / 2 - 100, WINSIZEX / 2 + 50, WINSIZEY / 2 - 50 };
RECT endBtn = { WINSIZEX / 2 - 150, WINSIZEY / 2, WINSIZEX / 2 + 50, WINSIZEY / 2 + 50 };
RECT retryBtn = { WINSIZEX / 2 - 30, WINSIZEY / 2 , WINSIZEX / 2 + 10, WINSIZEY / 2 + 10 };
POINT ptPos1;
POINT ptMouse;  // 마우스의 위치를 저장할 변수

// RECT를 만들어주는 함수
RECT RECT_MAKE(int x, int y, int size)
{
	RECT rt;
	rt.left = x;
	rt.right = rt.left + size;
	rt.top = y;
	rt.bottom = rt.top + size;

	return rt;
}

using namespace std;

struct tagBox
{
	RECT rt;
	float speed;
};

vector<tagBox> vecBox;	// 똥
int nDelay = 50;	 // 똥의 시간 간격
int nLevel;	// 난이도 
int nScore = 1;	// 유저의 점수
int time = 0;	// 시간
int hp = 1; // 플레이어의 hp

void loop()
{
	D2D1_POINT_2F offset = { 0, 0 };

	if (KeyBuffer[VK_LEFT] == KeyBuffer[VK_RIGHT])
		offset.x = 0.f;
	else if (KeyBuffer[VK_LEFT])
	{
		if (ptPos1.x > 0)
			offset.x = -10.f;
	}
	else
	{
		if (ptPos1.x < WINSIZEX - 50)
			offset.x = 10.f;
	}

	if (KeyBuffer[VK_UP] == KeyBuffer[VK_DOWN])
		offset.y = 0.f;
	else if (KeyBuffer[VK_UP])
	{
		if (ptPos1.y > 0)
			offset.y = -10.f;
	}
	else
	{
		if (ptPos1.y < WINSIZEY)
			offset.y = 10.f;
	}

	ptPos1.x += offset.x;
	ptPos1.y += offset.y;
}
