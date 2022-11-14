#include "framework.h"
#include "MainGame.h"

MainGame::MainGame()
{

}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	m_ptPos1 = { windows_size_width / 2, windows_size_height - 30 };   // 조작할 렉트의 좌표 값
	m_fMoveSpeed = 20;
	m_nScore = 0;
	m_nLevel = 0;

	m_isPicked = false;

	m_nDelay = 50;
}
	void MainGame::Update()
	{
		InvalidateRect(g_hWnd, NULL, true);   // 전체 영역을 다시 그린다. NULL이 들어가면 전체 화면.

		// 0x0001
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000) {
			if (m_rtBox1.left >= m_fMoveSpeed)
				m_ptPos1.x -= m_fMoveSpeed;
			else m_ptPos1.x = windows_size_width;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
			if (m_rtBox1.right <= windows_size_width - m_fMoveSpeed)
				m_ptPos1.x += m_fMoveSpeed;
			else m_ptPos1.x = 0;
		}

		m_nLevel = (m_nScore > 0) ? (m_nScore / 100 + 1) : 1;

		// 포지션 위치에 따른 렉트 정보 업데이트
		m_rtBox1 = RECT_MAKE(m_ptPos1.x, m_ptPos1.y, 50);

		if (m_nDelay >= 50) {

			RECT rt;
			tagBox box;

			box.rt.left = rand() % (windows_size_width - 30);
			box.rt.right = box.rt.left + 30;
			box.rt.top = -30;
			box.rt.bottom = 0;


			box.speed = rand() % 11 + 5;

			m_vecBox.push_back(box);

			m_nDelay = rand() % 20 + 30;
		}
		else m_nDelay += m_nLevel;

		std::vector<tagBox>::iterator iter;

		for (iter = m_vecBox.begin(); iter != m_vecBox.end(); iter++) {
			iter->rt.top += iter->speed;
			iter->rt.bottom += iter->speed;

			RECT rt;
			RECT rtIter = iter->rt;

			if (iter->rt.top > windows_size_height) {
				m_nScore++;
				m_vecBox.erase(iter);
				break;
			}
			else if (IntersectRect(&rt, &m_rtBox1, &rtIter)) {
				m_nScore -= 10;
				m_vecBox.erase(iter);
				break;
			}

		}

	}

	void MainGame::Render()
	{
		PAINTSTRUCT ps;
		// HDC : Device Context Handle : 출력을 위한 모든 데이터를 가지는 구조체
		HDC hdc = BeginPaint(g_hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		/*wstring wstr = L"코딩 지옥으로 입장을 허가합니다!!!";
		TextOut(hdc, 10, 10, wstr.c_str(), wstr.length());*/

		int roomSize = windows_size_height / 9;

		RECT_DRAW(m_rtBox1);

		for (auto& elem : m_vecBox) {
			RECT_DRAW(elem.rt);
		}


		char szBuf[32];

		_itoa_s(m_nLevel, szBuf, 10, 10); // 정수값을 문자열 값으로 변환해주는 함수
		std::string str = std::string(szBuf);
		TextOutA(hdc, 10, 10, str.c_str(), str.length());

		_itoa_s(m_nScore, szBuf, 10, 10); // 정수값을 문자열 값으로 변환해주는 함수
		str = std::string(szBuf);
		TextOutA(hdc, 10, 30, str.c_str(), str.length());


		EndPaint(g_hWnd, &ps);
	}