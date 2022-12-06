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
	case WM_CREATE:
	{
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
			srand((unsigned int)time(NULL));

			isStart = TRUE;
			userPos.x = WINSIZEX / 2;
			userPos.y = WINSIZEY / 2;

			// 플레이어와 똥을 그리고, 점수를 세기 위한 타이머
			SetTimer(hWnd, 1, 10, NULL);	
			// 시간을 측정하기 위한 타이머
			SetTimer(hWnd, 2, 1000, NULL);	
			// 패턴1을 위한 타이머
			SetTimer(hWnd, 3, 3000, NULL);
			// 하단패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 4, 10000, NULL);
			/*// 상단패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 5, 1000, NULL);
			// 오른쪽패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 6, 3000, NULL);
			// 좌측패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 7, 3000, NULL);*/
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
			userPos.y = WINSIZEY / 2;
			hp = 1;

			// 플레이어와 똥을 연산(?)하기 위한 타이머
			SetTimer(hWnd, 1, 10, NULL);	
			// 시간을 측정하기 위한 타이머
			SetTimer(hWnd, 2, 1000, NULL);	
			// 패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 3, 3000, NULL);
			// 하단패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 4, 10000, NULL);
			/*// 상단패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 5, 3000, NULL);
			// 우측패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 6, 3000, NULL);
			// 좌측패턴을 사용하기 위한 타이머
			SetTimer(hWnd, 7, 3000, NULL);*/
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
				
				if (nDelay >= 50)
				{
					int i = rand() % 2;
					int arr[2] = { 0, WINSIZEY - 50 };
					
					// 화살
					tagBox arrow;	
					arrow.rt.left = rand() % (WINSIZEX - 50);
					arrow.rt.right = arrow.rt.left + 10;
					arrow.rt.top = arr[i];
					arrow.rt.bottom = arrow.rt.top + 10;
					arrow.pos = userPos;

					arrowBox.push_back(arrow);
					nDelay = rand() % 30;
				}
				else
					nDelay +=1;
					
				vector<tagBox>::iterator iter;

				for (iter = arrowBox.begin(); iter != arrowBox.end(); iter++)
				{
					// 벡터의 좌표 구하기
					arrow_x = (iter->pos.x/2) - (iter->rt.left/2);	
					arrow_y = (iter->pos.y/2) - (iter->rt.top/2);

					// 화살이 생성된 위치와 플레이어 사이의 거리 구하기
					dis = sqrtf(powf(arrow_x, 2) + powf(arrow_y, 2));	

					// 벡터 노멀라이즈
					arrow_x = arrow_x / dis;
					arrow_y = arrow_y / dis;

					// 화살의 속도 정하기
					arrow_speed_x = arrow_x * 3.f;
					arrow_speed_y = arrow_y * 3.f;

					// iter에 들어있는 rt의 x와 y좌표에 arrow_speed_x와 arrow_speed_y를 더하기
					OffsetRect(&iter->rt, arrow_speed_x, arrow_speed_y);	

					// 화면 밖으로 나갈 수 있게 좌표 값 더해주기
					iter->pos.x += arrow_speed_x;
					iter->pos.y += arrow_speed_y;

					// IntersectRect를 사용하기 위한 RECT
					RECT rt;	
					// 편의를 위한 RECT
					RECT rtIter = iter->rt;	

					// 화살이 화면의 세로범위 밖으로 나갔을 때
					if (rtIter.bottom > WINSIZEY)
					{
						arrowBox.erase(iter);
						break;
					}
					// 화살이 화면의 세로범위 밖으로 나갔을 때
					else if (rtIter.top < 0)
					{
						arrowBox.erase(iter);
						break;
					}
					// 화살이 화면의 가로범위 밖으로 나갔을 때
					else if (rtIter.left < 0)
					{
						arrowBox.erase(iter);
						break;
					}
					// 화살이 화면의 가로범위 밖으로 나갔을 때
					else if (rtIter.right > WINSIZEX)
					{
						arrowBox.erase(iter);
						break;
					}
					// 유저와 화살이 닿았을 때
					else if (IntersectRect(&rt, &userRect, &rtIter))    
					{
						hp--;
						arrowBox.erase(iter);
						break;
					}
				}
				
				// 하단 패턴
				vector< bottomBox>::iterator b_iter;

				for (b_iter = btArrowBox.begin(); b_iter != btArrowBox.end(); b_iter++)
				{
					b_iter->rt.top -= 5;
					b_iter->rt.bottom -= 5;

					RECT b_rt;
					RECT rtbiter = b_iter->rt;

					// 화살이 화면의 세로범위 밖으로 나갔을 때
					if (rtbiter.top < 0)
					{
						btArrowBox.erase(b_iter);
						break;
					}
					// 유저와 화살이 닿았을 때
					else if (IntersectRect(&b_rt, &userRect, &rtbiter))
					{
						hp--;
						btArrowBox.erase(b_iter);
						break;
					}
				}
					// 상단 패턴
					vector< topBox>::iterator t_iter;

					for (t_iter = topArrowBox.begin(); t_iter != topArrowBox.end(); t_iter++)
					{
						t_iter->rt.top += 5;
						t_iter->rt.bottom += 5;

						RECT t_rt;
						RECT rttiter = t_iter->rt;

						// 화살이 화면의 세로범위 밖으로 나갔을 때
						if (rttiter.bottom > WINSIZEY)
						{
							topArrowBox.erase(t_iter);
							break;
						}
						// 유저와 화살이 닿았을 때
						else if (IntersectRect(&t_rt, &userRect, &rttiter))
						{
							hp--;
							topArrowBox.erase(t_iter);
							break;
						}
					}

					// 우측 패턴
					vector< rightBox>::iterator r_iter;

					for (r_iter = rightArrowBox.begin(); r_iter != rightArrowBox.end(); r_iter++)
					{
						r_iter->rt.left -= 5;
						r_iter->rt.right -= 5;

						RECT r_rt;
						RECT rtriter = r_iter->rt;

						// 화살이 화면의 가로범위 밖으로 나갔을 때
						if (rtriter.left < 0)
						{
							rightArrowBox.erase(r_iter);
							break;
						}
						// 유저와 화살이 닿았을 때
						else if (IntersectRect(&r_rt, &userRect, &rtriter))
						{
							hp--;
							rightArrowBox.erase(r_iter);
							break;
						}
					}

					// 좌측 패턴
					vector< leftBox>::iterator l_iter;

					for (l_iter = leftArrowBox.begin(); l_iter != leftArrowBox.end(); l_iter++)
					{
						l_iter->rt.right += 5;
						l_iter->rt.left += 5;

						RECT l_rt;
						RECT rtliter = l_iter->rt;

						// 화살이 화면의 가로범위 밖으로 나갔을 때
						if (rtliter.bottom > WINSIZEX)
						{
							leftArrowBox.erase(l_iter);
							break;
						}
						// 유저와 화살이 닿았을 때
						else if (IntersectRect(&l_rt, &userRect, &rtliter))
						{
							hp--;
							leftArrowBox.erase(l_iter);
							break;
						}
					}
			}
		}
		break;
		// 1초마다 세는 타이머
		case 2:    
		{
			if (isStart)
			{
				gtime++;
				nScore = gtime * 100.f;
			}
		}
		break;
		// 사방에서 화살이 나오는 패턴
		case 3:
		{
			int arr[16] = {10, 10, WINSIZEX / 2, 10, WINSIZEX - 10, 10, WINSIZEX - 10, WINSIZEY / 2, WINSIZEX - 100, WINSIZEY - 100, WINSIZEX / 2, WINSIZEY - 100, 10, WINSIZEY - 100, 10, WINSIZEY / 2};


			for (int j = 0; j < 15; j++)
			{
				// 화살
				tagBox arrow;
				arrow.rt.left = arr[j];
				arrow.rt.right = arrow.rt.left + 10;
				arrow.rt.top = arr[j + 1];
				arrow.rt.bottom = arrow.rt.top + 10;
				arrow.pos = userPos;

				j++;
				arrowBox.push_back(arrow);
			}
		}
		break;
		// 하단 패턴
		case 4:
		{
			int bottom_arr[7] = { 10, 125, 250, 375, 500, 625, 770 };

			rand_num = rand() % (7 - 5 + 1) + 5;

			for (int b = 0; b < 7; b++)
			{
				bottomBox bottom_arrow;
				bottom_arrow.rt.left = bottom_arr[b];
				bottom_arrow.rt.right = bottom_arrow.rt.left + 10;
				bottom_arrow.rt.top = WINSIZEY - 30;
				bottom_arrow.rt.bottom = bottom_arrow.rt.top + 10;

				btArrowBox.push_back(bottom_arrow);
			}
			// 랜덤 패턴 타이머를 호출
			SetTimer(hWnd, rand_num, 3000, NULL);
			// 자기 자신 종료
			KillTimer(hWnd, 4);
		}
		break;
		// 상단 패턴
		case 5:
		{
			int top_arr[7] = { 10, 125, 250, 375, 500, 625, 770 };

			int top_rand[3] = { 4, 6, 7 };
			int i = rand() % 3;

			rand_num = top_rand[i];

			for (int t = 0; t < 7; t++)
			{
				topBox top_arrow;
				top_arrow.rt.left = top_arr[t];
				top_arrow.rt.right = top_arrow.rt.left + 10;
				top_arrow.rt.top = 10;
				top_arrow.rt.bottom = top_arrow.rt.top + 10;

				topArrowBox.push_back(top_arrow);
			}
			// 랜덤 패턴 타이머를 호출
			SetTimer(hWnd, rand_num, 3000, NULL);
			// 자기 자신 종료
			KillTimer(hWnd, 5);
		}
		break;
		// 우측 패턴
		case 6:
		{
			int right_arr[6] = { 10, 114, 218, 322, 426, 520 };
			int right_rand[3] = { 4, 5, 7 };
			int i = rand() % 3;

			rand_num = right_rand[i];
			
			for (int r = 0; r < 6; r++)
			{
				rightBox right_arrow;
				right_arrow.rt.left = WINSIZEX;
				right_arrow.rt.right = right_arrow.rt.left + 10;
				right_arrow.rt.top = right_arr[r];
				right_arrow.rt.bottom = right_arrow.rt.top + 10;

				rightArrowBox.push_back(right_arrow);
			}
			// 랜덤 패턴 타이머를 호출
			SetTimer(hWnd, rand_num, 3000, NULL);
			// 자기 자신 종료
			KillTimer(hWnd, 6);
		}
		break;
		// 좌측 패턴
		case 7:
		{
			int left_arr[6] = { 10, 114, 218, 322, 426, 520 };

			rand_num = rand() % (6 - 4 + 1) + 4;

			for (int l = 0; l < 6; l++)
			{
				leftBox left_arrow;
				left_arrow.rt.left = 10;
				left_arrow.rt.right = left_arrow.rt.left + 10;
				left_arrow.rt.top = left_arr[l];
				left_arrow.rt.bottom = left_arrow.rt.top + 10;

				leftArrowBox.push_back(left_arrow);
			}
			// 랜덤 패턴 타이머를 호출
			SetTimer(hWnd, rand_num, 3000, NULL);
			// 자기 자신 종료
			KillTimer(hWnd, 7);
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
		memDC = CreateCompatibleDC(hdc);

		// 현재 윈도우 창 크기 받아오기
		RECT rect;
		GetClientRect(hWnd, &rect);
		// 더블 버퍼링
		// 메모리에 윈도우 창과 동일한 크기에 그릴수 있도록 셋팅하기 
		HBITMAP memBitmap = CreateCompatibleBitmap(memDC, rect.right, rect.bottom);
		// HBITMAP 또한 하나의 그리기 도구이므로 선택하기 및 예전 그리기 도구 저장
		HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);
		// 가상공간(memDC)의 백그라운드 컬러 설정해주기
		FillRect(memDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		// 메모리공간에 그림 그리기

		// 게임이 아직 시작되지 않았을 때
		if (!check)	
		{
			DRAW_RECT(memDC, startBtn);
			DRAW_RECT(memDC, endBtn);
			string str = "게임 시작";
			TextOutA(memDC, WINSIZEX / 2 - 90, WINSIZEY / 2 - 85, str.c_str(), str.length());
			str = "게임 종료";
			TextOutA(memDC, WINSIZEX / 2 - 90, WINSIZEY / 2 + 15, str.c_str(), str.length());

			check = TRUE;
		}
		// 게임이 시작 되었을 때
		if (isStart)	
		{
			// 플레이어  그리기
			DRAW_RECT(memDC, userRect);

			// 유저의 위치로 발사되는 화살 그리기
			for (int i = 0; i < arrowBox.size(); i++)	
			{
				DRAW_RECT(memDC, arrowBox[i].rt);
			}

			// 하단 패턴 화살 그리기
			for (int k = 0; k < btArrowBox.size(); k++)
			{
				DRAW_RECT(memDC, btArrowBox[k].rt);
			}

			// 상단 패턴 화살 그리기
			for (int o = 0; o < topArrowBox.size(); o++)
			{
				DRAW_RECT(memDC, topArrowBox[o].rt);
			}

			// 우측 패턴 화살 그리기
			for (int r = 0; r < rightArrowBox.size(); r++)
			{
				DRAW_RECT(memDC, rightArrowBox[r].rt);
			}

			// 좌측 패턴 화살 그리기
			for (int l = 0; l < leftArrowBox.size(); l++)
			{
				DRAW_RECT(memDC, leftArrowBox[l].rt);
			}

			char szBuf[32]; // 변환을 위한 변수

			// 문자열로 변환하기
			string str = string(szBuf);

			_itoa_s(nScore, szBuf, 10);
			str = string(szBuf);
			str = "당신의 점수: " + str;
			TextOutA(memDC, 10, 10, str.c_str(), str.length());

			_itoa_s(gtime, szBuf, 10);
			str = string(szBuf);
			str = "피한 시간: " + str + "초";
			TextOutA(memDC, 10, 30, str.c_str(), str.length());

			// 플레이어가 죽었을 때
			if (hp == 0)	
			{
				TextOutA(memDC, WINSIZEX / 2 - 50, WINSIZEY / 2 - 50, "GAME OVER", 9);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				KillTimer(hWnd, 5);
				KillTimer(hWnd, 6);
				KillTimer(hWnd, 7);
				TextOutA(memDC, retryBtn.left, retryBtn.top, "RETRY", 5);
				startBtn = { 0, 0, 0, 0 };
				endBtn = { 0, 0, 0, 0 };
				arrowBox.clear();
				btArrowBox.clear();
				topArrowBox.clear();
				rightArrowBox.clear();
				leftArrowBox.clear();
				gtime = 0;
				nScore = 0;
				nDelay = 50;
			}
		}

		// 가상 공간(memDC)에 그린 그림들을 메인 공간(hdc)로 전달
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
		// 생성해둔 메모리 공간 제거
		SelectObject(memDC, oldBitmap);
		DeleteObject(memBitmap);
		DeleteDC(memDC);
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
