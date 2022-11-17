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
#include <D2DBaseTypes.h>

// 윈도우 크기
#define WINSIZEX 640
#define WINSIZEY 720

using namespace std;

HWND g_hWnd;


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

// RECT를 그려주는 함수
void RECT_DRAW(RECT rect)
{
	HDC hdc = GetDC(g_hWnd);

	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

	ReleaseDC(g_hWnd, hdc);
}


