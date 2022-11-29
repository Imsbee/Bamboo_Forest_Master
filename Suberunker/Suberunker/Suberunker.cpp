// Suberunker.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Suberunker.h"
#include "framework.h"

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
		L"죽림고수",
		WS_OVERLAPPED | WS_SYSMENU,
		0,
		0,
		WINSIZEX,
		WINSIZEY,
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
	POINT pos = userPos;
	int i = rand() % 2;
	int arr[2] = { 0, WINSIZEY - 50 };

	tagBox arrow;	// 화살
	arrow.rt.left = rand() % (WINSIZEX - 50);
	arrow.rt.right = arrow.rt.left + 30;
	arrow.rt.top = arr[i];
	arrow.rt.bottom = arrow.rt.top + 30;

	arrow.speed = rand() % 12 + 5;

	vecBox.push_back(arrow);
	nDelay = rand() % 30;

	vector<tagBox>::iterator iter;

	for (iter = vecBox.begin(); iter != vecBox.end(); iter++)
	{
		arrow_x = pos.x - iter->rt.left;
		arrow_y = pos.y - iter->rt.top;
	
		dis = sqrtf(powf(arrow_x, 2) + powf(arrow_y, 2));	// 화살이 생성된 위치와 플레이어 사이의 거리 구하기

		// 벡터 정규화
		if (dis != 0)
		{
			arrow_x = arrow_x / dis;
			arrow_y = arrow_y / dis;
		}

		arrow_speed_x = arrow_x * 2.f;
		arrow_speed_y = arrow_y * 2.f;

		OffsetRect(&iter->rt, arrow_speed_x, arrow_speed_y);

		RECT rt;
		RECT rtIter = iter->rt;

		if (iter->rt.top > WINSIZEY)
		{
			vecBox.erase(iter);
			break;
		}
		else if (iter->rt.bottom < 0)
		{
			vecBox.erase(iter);
			break;
		}
		else if (iter->rt.left < 0)
		{
			vecBox.erase(iter);
			break;
		}
		else if (iter->rt.right > WINSIZEX)
		{
			vecBox.erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &userRect, &rtIter))
		{
			hp--;
			vecBox.erase(iter);
			break;
		}
		else if (PtInRect(&rtIter, ptMouse))
		{
			vecBox.erase(iter);
			break;
		}
	}

	return 1;
}

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
		RECT rt;
		HDC hdc = GetDC(hWnd);
		GetClientRect(hWnd, &rt);
		memDC = CreateCompatibleDC(hdc);
		memBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

		FillRect(memDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, memDC, 0, 0, SRCCOPY);

		ReleaseDC(hWnd, hdc);

		MAKE_ARROW(NULL);
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (isStart)
		{
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (!isStart)
		{
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
		}

		if (PtInRect(&startBtn, ptMouse))	// 스타트 버튼을 눌렀을 때
		{
			isStart = TRUE;
			userPos.x = WINSIZEX / 2;
			userPos.y = WINSIZEY - 100;

			SetTimer(hWnd, 1, 10, NULL);	// 플레이어와 똥을 그리고, 점수를 세기 위한 타이머
			SetTimer(hWnd, 2, 1000, NULL);	// 시간을 측정하기 위한 타이머
		}
		if (PtInRect(&endBtn, ptMouse))	// 종료 버튼을 눌렀을 때
		{
			exit(0);
		}
		if (PtInRect(&retryBtn, ptMouse))	 // 다시 시작 버튼을 눌렀을 때
		{
			userPos.x = WINSIZEX / 2;
			userPos.y = WINSIZEY - 100;
			hp = 1;

			SetTimer(hWnd, 1, 10, NULL);	// 플레이어와 똥을 연산(?)하기 위한 타이머
			SetTimer(hWnd, 2, 1000, NULL);	// 시간을 측정하기 위한 타이머
		}
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
			if (isStart)
			{
				loop();

				InvalidateRect(hWnd, NULL, TRUE);

				userRect = RECT_MAKE(userPos.x, userPos.y, 30);	// 플레이어 그리기

				if (nDelay >= 30)
				{
					
				}
				else
					nDelay +=1;

				
			}
		}
		break;
		case 2:
		{
			if (isStart)
			{
				time++;
				nScore = time * 100.f;
			}
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
		if (!check)	// 게임이 아직 시작되지 않았을 때
		{
			DRAW_RECT(hdc, startBtn);
			DRAW_RECT(hdc, endBtn);
			string str = "게임 시작";
			TextOutA(hdc, WINSIZEX / 2 - 90, WINSIZEY / 2 - 85, str.c_str(), str.length());
			str = "게임 종료";
			TextOutA(hdc, WINSIZEX / 2 - 90, WINSIZEY / 2 + 15, str.c_str(), str.length());

			check = TRUE;
		}

		if (isStart)	// 게임이 시작 되었을 때
		{
			DRAW_RECT(hdc, userRect);	// 플레이어  그리기

			for (int i = 0; i < vecBox.size(); i++)	// 똥 그리기
			{
				DRAW_RECT(hdc, vecBox[i].rt);	
			}

			char szBuf[32]; // 변환을 위한 변수

			// 문자열로 변환하기
			_itoa_s(nLevel, szBuf, 10);
			string str = string(szBuf);
			str = "Level: " + str;
			TextOutA(hdc, 10, 10, str.c_str(), str.length());

			_itoa_s(nScore, szBuf, 10);
			str = string(szBuf);
			str = "당신의 점수: " + str;
			TextOutA(hdc, 10, 30, str.c_str(), str.length());

			_itoa_s(time, szBuf, 10);
			str = string(szBuf);
			str = "피한 시간: " + str + "초";
			TextOutA(hdc, 10, 50, str.c_str(), str.length());

			_itoa_s(hp, szBuf, 10);
			str = string(szBuf);
			str = "당신의 체력: " + str;
			TextOutA(hdc, 10, 70, str.c_str(), str.length());

			if (hp == 0)	// 플레이어가 죽었을 때
			{
				TextOutA(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2 - 50, "GAME OVER", 9);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				TextOutA(hdc, retryBtn.left, retryBtn.top, "RETRY", 5);
				startBtn = { 0, 0, 0, 0 };
				endBtn = { 0, 0, 0, 0 };
				vecBox.clear();
				time = 0;
				nScore = 0;
				nLevel = 0;
				nDelay = 50;
			}
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
