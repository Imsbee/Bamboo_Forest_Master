// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW
	(
		szWindowClass,
		L"죽림고수",    // 제목
		WS_OVERLAPPED | WS_SYSMENU,
		0,
		0,
		WINSIZEX,        // 창의 가로 크기
		WINSIZEY,        // 창의 세로 크기
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

DWORD WINAPI MAKE_ARROW(LPVOID lpvoid)
{
	


	

	return 0;
}


//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
	{
		userPos = { WINSIZEX / 2 - 30, WINSIZEY - 100 };		// 플레이어의 시작 위치 지정
		SetTimer(hWnd, 1, 10, NULL);										// 1번 타이머 설정
		SetTimer(hWnd, 2, 1000, NULL);
	}
	break;
	case WM_KEYDOWN:
	{
		KeyBuffer[wParam] = TRUE;
	}
	break;
	case WM_KEYUP:
	{
		KeyBuffer[wParam] = FALSE;
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			loop();	    // 플레이어의 움직임을 연산해주는 함수 호출
			userRect = MAKE_RECT(userPos.x, userPos.y, 30);    // 플레이어의 RECT 생성
			InvalidateRect(hWnd, NULL, FALSE);    // 화면 무효화 호출

			if (Delay >= 30)
			{
				// 화살의 y 좌표를 정하기
				int i = rand() % 2;
				int arr[2] = { 0, WINSIZEY - 100 };

				

				arrowBox arrow;    // 화살의 RECT
				arrow.rt.left = rand() % (WINSIZEX - 50);
				arrow.rt.right = arrow.rt.left + 30;
				arrow.rt.top = arr[i];
				arrow.rt.bottom = arrow.rt.top + 30;

				arrowVec.push_back(arrow);
				Delay = rand() % 30;
			}
			else
				Delay += 1;

			vector<arrowBox>::iterator iter;

			for (iter = arrowVec.begin(); iter != arrowVec.end(); iter++)
			{
				// 화살의 각도 정하기
				arrow_x = userRect.left - iter->rt.left;
				arrow_y = userRect.top - iter->rt.top;
				dis = sqrtf(powf(arrow_x, 2) + powf(arrow_y, 2));
				arrow_x = arrow_x / dis;
				arrow_y = arrow_y / dis;

				arrow_speed_x = arrow_x * 2.f;
				arrow_speed_y = arrow_y * 2.f;

				OffsetRect(&iter->rt, arrow_speed_x, arrow_speed_y);

				RECT rt;
				RECT rtIter = iter->rt;

				if (rtIter.top > WINSIZEY)
				{
					arrowVec.erase(iter);
					break;
				}
				else if (rtIter.bottom < 0)
				{
					arrowVec.erase(iter);
					break;
				}
				else if (rtIter.left < 0)
				{
					arrowVec.erase(iter);
					break;
				}
				else if (rtIter.right > WINSIZEX)
				{
					arrowVec.erase(iter);
					break;
				}
				else if (IntersectRect(&rt, &userRect, &rtIter))
				{
					arrowVec.erase(iter);
					break;
				}

			}
		}
		break;
		case 2:
		{
		}
		break;
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		// 메모리에 DC 가지고 생성
		HDC memdc = CreateCompatibleDC(hdc);
		// 현재 윈도우 창 크기 받아오기
		RECT rect;
		GetClientRect(hWnd, &rect);

		// !! 더블 버퍼링 사용 !!
		// 메모리에 윈도우 창과 동일한 크기에 그릴수 있도록 셋팅하기 
		HBITMAP memBitmap = CreateCompatibleBitmap(memdc, rect.right, rect.bottom);
		// HBITMAP 또한 하나의 그리기 도구이므로 선택하기 및 예전 그리기 도구 저장
		HBITMAP oldBitmap = (HBITMAP)SelectObject(memdc, memBitmap);
		// 가상공간(memdc)의 백그라운드 컬러 설정해주기
		FillRect(memdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		// 메모리공간에 그림 그리기

		DRAW_RECT(memdc, userRect);    // 유저를 가상공간(memdc)에 그리기

		for (int i = 0; i < arrowVec.size(); i++)
		{
			DRAW_RECT(memdc, arrowVec[i].rt);
		}


		//넘겨주고자 하는 메인 윈도우로 전달하기 (메모리공간 그림 --> 메인 화면)
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, memdc, 0, 0, SRCCOPY);
		//생성해둔 메모리 공간 제거
		SelectObject(memdc, oldBitmap);
		DeleteObject(memBitmap);
		DeleteDC(memdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
