#include "MainGame.h"

MainGame::MainGame() { }

MainGame::~MainGame() { }

void MainGame::Init()
{
	m_ptPos1 = { windows_size_width / 2 - 50, windows_size_height - 100 };	// 플레이어의 위치 초기화
	m_fMoveSpeed = 20;	// 똥의 스피드 초기화
	m_nScore = 0;	// 점수 초기화
	m_nLevel = 0;	// 레벨 초기화
	m_nHp = 5;		// hp 초기화
	m_nTime = 0;	// 시간 초기화
	m_isPicked = FALSE;
	m_nDelay = 50;
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, TRUE);

	loop();

	m_nLevel = (m_nScore > 0) ? (m_nScore / 100 + 1) : 1;	// 레벨 값 주기
	m_rtBox1 = RECT_MAKE(m_ptPos1.x, m_ptPos1.y, 30);	// 플레이어 RECT 생성
	
	if (m_nDelay >= 50)
	{
		RECT rt;
		tagBox box;

		box.rt.left = rand() % (windows_size_width - 100);
		box.rt.right = box.rt.left + 30;
		box.rt.top = -30;
		box.rt.bottom = 0;

		box.speed = rand() % 11 + 5;
		m_vecBox.push_back(box);
		m_nDelay = rand() % 20 + 30;
	}
	else
		m_nDelay += m_nLevel;

	std::vector<tagBox>::iterator iter;

	for (iter = m_vecBox.begin(); iter != m_vecBox.end(); iter++)
	{
		iter->rt.top += iter->speed;
		iter->rt.bottom += iter->speed;

		RECT rt;
		RECT rtIter = iter->rt;

		if (iter->rt.top > windows_size_height)
		{
			m_nScore++;
			m_vecBox.erase(iter);
			break;
		}
		else if (IntersectRect(&rt, &m_rtBox1, &rtIter))
		{
			m_nHp--;
			m_vecBox.erase(iter);
			break;
		}
	}
}

void MainGame::Render()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(g_hWnd, &ps);

	Rectangle(hdc, m_rtBox1.left, m_rtBox1.top, m_rtBox1.right, m_rtBox1.bottom);

	for (auto& elem : m_vecBox)
	{
		Rectangle(hdc, elem.rt.left, elem.rt.top, elem.rt.right, elem.rt.bottom);
	}

	char szBuf[32];

	// 문자열로 변환하기
	_itoa_s(m_nLevel, szBuf, 10);
	std::string str = std::string(szBuf);
	str = "Level: " + str;
	TextOutA(hdc, 10, 10, str.c_str(), str.length());

	_itoa_s(m_nScore, szBuf, 10);
	str = std::string(szBuf);
	str = "당신의 점수: " + str;
	TextOutA(hdc, 10, 30, str.c_str(), str.length());

	_itoa_s(m_nTime, szBuf, 10);
	str = std::string(szBuf);
	str = "피한 시간: " + str + "초";
	TextOutA(hdc, 10, 50, str.c_str(), str.length());

	_itoa_s(m_nHp, szBuf, 10);
	str = std::string(szBuf);
	str = "당신의 체력: " + str;
	TextOutA(hdc, 10, 70, str.c_str(), str.length());

	EndPaint(g_hWnd, &ps);
}

void MainGame::Start()
{

}

void MainGame::Exit()
{

}