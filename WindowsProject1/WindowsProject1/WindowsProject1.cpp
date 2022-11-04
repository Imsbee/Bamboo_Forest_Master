// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
int user_hp = 500;	// 유저의 hp
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
BOOL KeyBuffer[256];		// 키의 눌림 상태를 확인해주는 변수
POINT user_pos = { 600, 400 };		// 유저의 위치 변수
POINT monster_pos = { 1300, 10 };	// 몬스터의 위치 변수
POINT monster_attack_pos;
RECT monster_attack_rect;
RECT user;		// 유저의 RECT 
RECT user_hp_rect;	// 유저 hp의 RECT
HBITMAP memBitmap;  // 메모리 DC에서 사용할 Bitmap 값
HDC memdc;      // 메모리 DC 값


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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

// 유저의 움직임을 연산해주는 함수
void loop()	
{
	D2D1_POINT_2F offset;

	if (KeyBuffer[VK_LEFT] == KeyBuffer[VK_RIGHT])
		offset.x = 0.f;
	else if (KeyBuffer[VK_LEFT])
		offset.x = -10.f;
	else
		offset.x = 10.f;

	if (KeyBuffer[VK_UP] == KeyBuffer[VK_DOWN])
		offset.y = 0.f;
	else if (KeyBuffer[VK_UP])
		offset.y = -10.f;
	else
		offset.y = 10.f;

	user_pos.x += offset.x;
	user_pos.y += offset.y;
}

// 몬스터의 움직임을 연산해주는 쓰레드
DWORD WINAPI monsterMove(LPVOID lpvoid)
{
	RECT monster = { monster_pos.x, monster_pos.y, monster_pos.x + 50, monster_pos.y + 50 };
	
	if (monster_pos.y == 10)
	{
		while (monster_pos.y != 630)
		{
			monster_pos.y += 10;
			Sleep(30);
		}
	}
	else if (monster_pos.y == 630)
	{
		while (monster_pos.y != 10)
		{
			monster_pos.y -= 10;
			Sleep(30);
		}
		
	}
	
	return 0;
}

// 몬스터의 공격을 연산해주는 쓰레드
DWORD WINAPI monster_attack(LPVOID lpvoid)
{
	monster_attack_pos = { monster_pos.x, monster_pos.y };
	monster_attack_rect = { monster_attack_pos.x, monster_attack_pos.y, monster_attack_pos.x + 30, monster_attack_pos.y + 30 };

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
	RECT rect;
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
		// memBitmap 그리고 memDC 생성하기 위한 과정
		hdc = GetDC(hWnd);
		memdc = CreateCompatibleDC(hdc);

		GetClientRect(hWnd, &rect);     // 현재 윈도우 창 크기 받아오기
		memBitmap = CreateCompatibleBitmap(memdc, rect.right, rect.bottom);     // 사용자의 화면과 같은 크기의 비트맵 생성
		SelectObject(memdc, memBitmap);
		FillRect(memdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));    // 화면 전체를 흰색으로 칠하기(배경색 지정)
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, memdc, 0, 0, SRCCOPY);   // memdc에 그린 내용을 hdc에 고속 복사

		ReleaseDC(hWnd, hdc);
		SetTimer(hWnd, 0, 10, NULL);	// 유저의 움직임을 연산해주는 함수를 호출하기 위한 타이머
		SetTimer(hWnd, 1, 500, NULL);
		
		user_hp_rect = { 10, 10,  user_hp, 30 };
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 0:
		{
			loop(); // 유저의 움직임을 연산해주는 함수
			user = { user_pos.x, user_pos.y, user_pos.x + 30, user_pos.y + 30 };
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		case 1:
		{
			CreateThread(NULL, NULL, monsterMove, NULL, NULL, NULL);
			
		}
		break;
		}
	}
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		Rectangle(hdc, user.left, user.top, user.right, user.bottom);	// 유저
		Rectangle(hdc, monster_pos.x, monster_pos.y, monster_pos.x + 50, monster_pos.y + 50);	// 몬스터
		Rectangle(hdc, 10, 10, user_hp, 30);	// 유저의 체력
		FillRect(hdc, &user_hp_rect, brush);
		Rectangle(hdc, monster_attack_rect.left, monster_attack_rect.top, monster_attack_rect.right, monster_attack_rect.bottom);

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
