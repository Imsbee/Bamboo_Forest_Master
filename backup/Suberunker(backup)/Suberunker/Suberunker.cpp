// Suberunker.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Suberunker.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
POINT ptMouse;  // 마우스의 위치를 저장할 변수
POINT ptPos1;	// 플레이어의 위치
RECT rtBox1;	// 플레이어의 RECT
BOOL KeyBuffer[256];	// 키가 눌렸는지 확인하기 위한 배열

struct tagBox
{
	RECT rt;
	float speed;
};

std::vector<tagBox> vecBox;	// 똥
int nDelay = 50;	 // 똥의 시간 간격
int nLevel;	// 난이도 
int nScore = 1;	// 유저의 점수
int time = 0;	// 시간
int hp = 5; // 플레이어의 hp

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
	LoadStringW(hInstance, IDC_SUBERUNKER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUBERUNKER));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUBERUNKER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SUBERUNKER);
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
		szTitle,
		WS_OVERLAPPED | WS_SYSMENU,
		0,
		0,
		windows_size_width,
		windows_size_height,
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


void loop()
{
	D2D1_POINT_2F offset = { 0, 0 };

	if (KeyBuffer[VK_LEFT] == KeyBuffer[VK_RIGHT])
		offset.x = 0.f;
	else if (KeyBuffer[VK_LEFT])
	{
		if(ptPos1.x > 0)
			offset.x = -10.f;
	}
	else
	{
		if(ptPos1.x < windows_size_width - 50)
			offset.x = 10.f;
	}

	ptPos1.x += offset.x;
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
		ptPos1.y = windows_size_height - 100;

		SetTimer(hWnd, 1, 10, NULL);	// 플레이어와 똥을 그리고, 점수를 세기 위한 타이머
		SetTimer(hWnd, 2, 1000, NULL);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
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
		switch(wParam)
		{
		case 1:
		{
			loop();

			InvalidateRect(hWnd, NULL, TRUE);

			nLevel = nScore / 100 + 1;

			rtBox1 = RECT_MAKE(ptPos1.x, ptPos1.y, 30);	// 플레이어 그리기

			if (nDelay >= 50)
			{
				tagBox box;	// 똥
				box.rt.left = rand() % (windows_size_width - 50);
				box.rt.right = box.rt.left + 30;
				box.rt.top = -30;
				box.rt.bottom = 0;

				box.speed = rand() % 12 + 5;

				vecBox.push_back(box);
				nDelay = rand() % 50;
			}
			else
				nDelay += nLevel;

			std::vector<tagBox>::iterator iter;

			for (iter = vecBox.begin(); iter != vecBox.end(); iter++)
			{
				iter->rt.top += iter->speed;
				iter->rt.bottom += iter->speed;

				RECT rt;
				RECT rtIter = iter->rt;

				if (iter->rt.top > windows_size_height)
				{
					nScore++;
					vecBox.erase(iter);
					break;
				}
				else if (IntersectRect(&rt, &rtBox1, &rtIter))
				{
					hp--;
					vecBox.erase(iter);
					break;
				}
				else if (PtInRect(&rtIter, ptMouse))
				{
					nScore += 5;
					vecBox.erase(iter);
					break;
				}
			}
		}
		break;
		case 2:
		{
			time++;
		}
		break;
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		Rectangle(hdc, rtBox1.left, rtBox1.top, rtBox1.right, rtBox1.bottom);	// 플레이어 그리기

		for (int i = 0; i < vecBox.size(); i++)
		{
			Rectangle(hdc, vecBox[i].rt.left, vecBox[i].rt.top, vecBox[i].rt.right, vecBox[i].rt.bottom);
		}

		char szBuf[32]; // 변환을 위한 변수

		// 문자열로 변환하기
		_itoa_s(nLevel, szBuf, 10);
		std::string str = std::string(szBuf);
		str = "Level: " + str;
		TextOutA(hdc, 10, 10, str.c_str(), str.length());

		_itoa_s(nScore, szBuf, 10);
		str = std::string(szBuf);
		str = "당신의 점수: " + str;
		TextOutA(hdc, 10, 30, str.c_str(), str.length());

		_itoa_s(time, szBuf, 10);
		str = std::string(szBuf);
		str = "피한 시간: " + str + "초";
		TextOutA(hdc, 10, 50, str.c_str(), str.length());

		_itoa_s(hp, szBuf, 10);
		str = std::string(szBuf);
		str = "당신의 체력: " + str;
		TextOutA(hdc, 10, 70, str.c_str(), str.length());

		if (hp == 0)
		{
			TextOutA(hdc, windows_size_width / 2 - 50, windows_size_height / 2 - 50, "GAME OVER", 9);
			KillTimer(hWnd, 1);
		}

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
