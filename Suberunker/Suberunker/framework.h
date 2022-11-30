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

using namespace std;

// 유저와 관련된 변수들
RECT userRect;	// 플레이어의 RECT
POINT userPos;	// 플레이어의 위치
POINT ptMouse;  // 마우스의 위치를 저장할 변수
int hp = 1;		// 플레이어의 hp

// 화살과 관련된 변수들
// 화살을 담을 구조체
struct tagBox
{
	RECT rt;
};
float arrow_speed_x;		// 화살의 x좌표 속도
float arrow_speed_y;		// 화살의 y좌표 속도
float dis;					// 화살과 플레이어 사이의 거리
float arrow_x;				// 화살의 x 좌표
float arrow_y;				// 화살의 y 좌표
vector<tagBox> arrowBox;	// 화살을 담을 벡터구조체


// 부가적인 변수들
int nDelay = 50;		// 화살의 시간 간격
int nLevel;				// 화살의 발생 시간 간격을 조절하기 위한 난이도 변수
float nScore = 1;		// 유저의 점수
float time = 1.f;		// 시간
BOOL check;				// 게임 시작 버튼과 종료 버튼을 출력하기 위해 상태를 체크해주는 변수
BOOL isStart;			// 게임이 시작되었는지 판단하는 변수
BOOL KeyBuffer[256];	// 플레이어가 누른 wParam값을 TRUE로 변경하기 위한 변수
RECT startBtn = { WINSIZEX / 2 - 150, WINSIZEY / 2 - 100, WINSIZEX / 2 + 50, WINSIZEY / 2 - 50 };	// 시작 버튼
RECT endBtn = { WINSIZEX / 2 - 150, WINSIZEY / 2, WINSIZEX / 2 + 50, WINSIZEY / 2 + 50 };			// 종료 버튼
RECT retryBtn = { WINSIZEX / 2 - 35, WINSIZEY / 2 , WINSIZEX / 2 + 10, WINSIZEY / 2 + 10 };			// 다시 시작 버튼
HDC memDC;				// 가상공간에서 사용할 DC
HBITMAP memBitmap;		// 가상 공간에서 사용할 Bitmap
HBITMAP oldBitmap;		// 원래 사용하던 Bitmap을 저장하기 위한 Bitmap


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

// RECT를 그리는 함수
void DRAW_RECT(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

// 플레이어의 움직임을 연산하기 위한 함수
void loop()
{
	// 이동 값을 +하기 위한 변수
	D2D1_POINT_2F offset = { 0, 0 };	

	// 둘다 FALSE인 경우 값을 더하지 않음
	if (KeyBuffer[VK_LEFT] == KeyBuffer[VK_RIGHT])	
		offset.x = 0.f;
	// 왼쪽 버튼을 누른 경우
	else if (KeyBuffer[VK_LEFT])	
	{
		// 그라운드 밖으로 나가게 하지 않기 위한 if문
		if (userPos.x > 0)	 
			offset.x = -10.f;
	}
	// 오른쪽 버튼을 누른 경우
	else 
	{
		// 그라운드 밖으로 나가게 하지 않기 위한 if문
		if (userPos.x < WINSIZEX - 50)	
			offset.x = 10.f;
	}
	// 둘다 FALSE인 경우 값을 더하지 않음
	if (KeyBuffer[VK_UP] == KeyBuffer[VK_DOWN])	
		offset.y = 0.f;
	// 위쪽 버튼을 누른 경우
	else if (KeyBuffer[VK_UP])	
	{
		// 그라운드 밖으로 나가게 하지 않기 위한 if문
		if (userPos.y > 0)	
			offset.y = -10.f;
	}
	// 아래쪽 버튼을 누른 경우
	else 
	{
		// 그라운드 밖으로 나가게 하지 않기 위한 if문
		if (userPos.y < WINSIZEY - 100)	
			offset.y = 10.f;
	}

	// 플레이어의 위치에 offset값을 더해서 플레이어 움직이기
	userPos.x += offset.x;
	userPos.y += offset.y;
}
