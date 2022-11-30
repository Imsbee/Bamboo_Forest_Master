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
		// 게임이 아직 시작되지 않았을 때
		if (!isStart)
		{
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
		}
		// 스타트 버튼을 눌렀을 때
		if (PtInRect(&startBtn, ptMouse))	
		{
			isStart = TRUE;
			userPos.x = WINSIZEX / 2;
			userPos.y = WINSIZEY - 100;

			// 플레이어와 똥을 그리고, 점수를 세기 위한 타이머
			SetTimer(hWnd, 1, 10, NULL);	
			// 시간을 측정하기 위한 타이머
			SetTimer(hWnd, 2, 1000, NULL);	
		}
		// 종료 버튼을 눌렀을 때
		if (PtInRect(&endBtn, ptMouse))	
		{
			exit(0);
		}
		// 다시 시작 버튼을 눌렀을 때
		if (PtInRect(&retryBtn, ptMouse))	 
		{
			userPos.x = WINSIZEX / 2;
			userPos.y = WINSIZEY - 100;
			hp = 1;

			// 플레이어와 똥을 연산(?)하기 위한 타이머
			SetTimer(hWnd, 1, 10, NULL);	
			// 시간을 측정하기 위한 타이머
			SetTimer(hWnd, 2, 1000, NULL);	
		}
	}
	break;
	case WM_KEYDOWN:
	{
		// 누른 키의 bool을 true로 설정
		KeyBuffer[wParam] = TRUE;
	}
	break;
	case WM_KEYUP:
	{
		// 누른 키의 bool을 false로 설정
		KeyBuffer[wParam] = FALSE;
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		// 0.01초마다 세는 타이머
		case 1:
		{
			// 게임이 시작되었을 때
			if (isStart)    
			{
				// 플레이어의 움직임을 연산하는 함수
				loop();	
				// 화면 무효화 호출
				InvalidateRect(hWnd, NULL, FALSE);	

				// 크기가 20인 플레이어 그리기
				userRect = RECT_MAKE(userPos.x, userPos.y, 20);	

				if (nDelay >= 30)
				{
					int i = rand() % 2;
					int arr[2] = { 0, WINSIZEY - 50 };

					// 화살
					tagBox arrow;	
					arrow.rt.left = rand() % (WINSIZEX - 50);
					arrow.rt.right = arrow.rt.left + 10;
					arrow.rt.top = arr[i];
					arrow.rt.bottom = arrow.rt.top + 10;

					arrowBox.push_back(arrow);
					nDelay = rand() % 30;
				}
				else
					nDelay +=1;

				vector<tagBox>::iterator iter;

				for (iter = arrowBox.begin(); iter != arrowBox.end(); iter++)
				{
					// 벡터의 좌표 구하기
					arrow_x = userPos.x - iter->rt.left;	
					arrow_y = userPos.y - iter->rt.top;

					// 화살이 생성된 위치와 플레이어 사이의 거리 구하기
					dis = sqrtf(powf(arrow_x, 2) + powf(arrow_y, 2));	
					
					// 벡터 정규화
					arrow_x = arrow_x / dis;
					arrow_y = arrow_y / dis;

					// 화살의 속도 정하기
					arrow_speed_x = arrow_x * 2.f;
					arrow_speed_y = arrow_y * 2.f;

					OffsetRect(&iter->rt, arrow_speed_x, arrow_speed_y);	// iter에 들어있는 rt의 x와 y좌표에 arrow_speed_x와 arrow_speed_y를 더하기

					RECT rt;
					RECT rtIter = iter->rt;

					if (iter->rt.top > WINSIZEY)    // 화살이 화면의 세로범위 밖으로 나갔을 때
					{
						arrowBox.erase(iter);
						break;
					}
					else if (iter->rt.bottom < 0)    // 화살이 화면의 세로범위 밖으로 나갔을 때
					{
						arrowBox.erase(iter);
						break;
					}
					else if (iter->rt.left < 0)    // 화살이 화면의 가로범위 밖으로 나갔을 때
					{
						arrowBox.erase(iter);
						break;
					}
					else if (iter->rt.right > WINSIZEX)    // 화살이 화면의 가로범위 밖으로 나갔을 때
					{
						arrowBox.erase(iter);
						break;
					}
					else if (IntersectRect(&rt, &userRect, &rtIter))    // 유저와 화살이 닿았을 때
					{
						hp--;
						arrowBox.erase(iter);
						break;
					}
					/*
					else if (PtInRect(&rtIter, ptMouse))    // 마우스 포인터가 화살에 닿았을 때
					{
						arrowBox.erase(iter);
						break;
					}
					*/
				}

			}
		}
		break;
		// 1초마다 세는 타이머
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

		if (!check)	// 게임이 아직 시작되지 않았을 때
		{
			DRAW_RECT(memdc, startBtn);
			DRAW_RECT(memdc, endBtn);
			string str = "게임 시작";
			TextOutA(memdc, WINSIZEX / 2 - 90, WINSIZEY / 2 - 85, str.c_str(), str.length());
			str = "게임 종료";
			TextOutA(memdc, WINSIZEX / 2 - 90, WINSIZEY / 2 + 15, str.c_str(), str.length());

			check = TRUE;
		}

		if (isStart)	// 게임이 시작 되었을 때
		{
			DRAW_RECT(memdc, userRect);	// 플레이어  그리기

			for (int i = 0; i < arrowBox.size(); i++)	// 똥 그리기
			{
				DRAW_RECT(memdc, arrowBox[i].rt);
			}

			char szBuf[32]; // 변환을 위한 변수

			// 문자열로 변환하기
			_itoa_s(nLevel, szBuf, 10);
			string str = string(szBuf);
			str = "Level: " + str;
			TextOutA(memdc, 10, 10, str.c_str(), str.length());

			_itoa_s(nScore, szBuf, 10);
			str = string(szBuf);
			str = "당신의 점수: " + str;
			TextOutA(memdc, 10, 30, str.c_str(), str.length());

			_itoa_s(time, szBuf, 10);
			str = string(szBuf);
			str = "피한 시간: " + str + "초";
			TextOutA(memdc, 10, 50, str.c_str(), str.length());

			_itoa_s(hp, szBuf, 10);
			str = string(szBuf);
			str = "당신의 체력: " + str;
			TextOutA(memdc, 10, 70, str.c_str(), str.length());

			if (hp == 0)	// 플레이어가 죽었을 때
			{
				TextOutA(memdc, WINSIZEX / 2 - 50, WINSIZEY / 2 - 50, "GAME OVER", 9);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				TextOutA(memdc, retryBtn.left, retryBtn.top, "RETRY", 5);
				startBtn = { 0, 0, 0, 0 };
				endBtn = { 0, 0, 0, 0 };
				arrowBox.clear();
				time = 0;
				nScore = 0;
				nLevel = 0;
				nDelay = 50;
			}
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
