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
#include <D2DBaseTypes.h>
#include <vector>

// 윈도우 크기
#define WINSIZEX 1280
#define WINSIZEY 760

using namespace std;

int Delay;


// 유저와 관련된 변수들
POINT userPos;    // 유저의 위치 좌표를 나타내는 변수
RECT userRect;	   // 유저의 RECT

// 화살과 관련된 변수들 
struct arrowBox
{
	RECT rt;
};
vector<arrowBox> arrowVec;
float arrow_x, arrow_y, dis;    // 화살의 x, y 좌표와 화살과 플레이어 사이의 거리
float arrow_speed_x, arrow_speed_y;

// 어떤 키가 눌렸는지 확인해줄 BOOL 변수
BOOL KeyBuffer[256];

// RECT를 만들어주는 함수
RECT MAKE_RECT(int x, int y, int size)
{
	RECT rt;
	rt.left = x;
	rt.right = rt.left + size;
	rt.top = y;
	rt.bottom = rt.top + size;

	return rt;
}

// RECT를 그리는 함수
void DRAW_RECT(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

// 플레이어의 움직임을 연산하기 위한 함수
void loop()
{
	D2D1_POINT_2F offset = { 0, 0 };	// 이동 값을 +하기 위한 변수

	if (KeyBuffer[VK_LEFT] == KeyBuffer[VK_RIGHT])	// 둘다 FALSE인 경우 값을 더하지 않음
		offset.x = 0.f;
	else if (KeyBuffer[VK_LEFT])	// 왼쪽 버튼을 누른 경우
	{
		if (userPos.x > 0)	 // 그라운드 밖으로 나가게 하지 않기 위한 if문
			offset.x = -10.f;
	}
	else // 오른쪽 버튼을 누른 경우
	{
		if (userPos.x < WINSIZEX - 50)	// 그라운드 밖으로 나가게 하지 않기 위한 if문
			offset.x = 10.f;
	}

	if (KeyBuffer[VK_UP] == KeyBuffer[VK_DOWN])	// 둘다 FALSE인 경우 값을 더하지 않음
		offset.y = 0.f;
	else if (KeyBuffer[VK_UP])	// 위쪽 버튼을 누른 경우
	{
		if (userPos.y > 0)	// 그라운드 밖으로 나가게 하지 않기 위한 if문
			offset.y = -10.f;
	}
	else // 아래쪽 버튼을 누른 경우
	{
		if (userPos.y < WINSIZEY - 100)	// 그라운드 밖으로 나가게 하지 않기 위한 if문
			offset.y = 10.f;
	}

	// 플레이어의 위치에 offset값을 더해서 플레이어 움직이기
	userPos.x += offset.x;
	userPos.y += offset.y;
}