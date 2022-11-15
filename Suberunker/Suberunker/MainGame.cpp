#include "MainGame.h"

MainGame::MainGame() { }

MainGame::~MainGame() { }

void MainGame::Init()
{
	m_ptPos1 = { windows_size_width / 2 - 50, windows_size_height - 100 };	// �÷��̾��� ��ġ �ʱ�ȭ
	m_fMoveSpeed = 20;	// ���� ���ǵ� �ʱ�ȭ
	m_nScore = 0;	// ���� �ʱ�ȭ
	m_nLevel = 0;	// ���� �ʱ�ȭ
	m_nHp = 5;		// hp �ʱ�ȭ
	m_nTime = 0;	// �ð� �ʱ�ȭ
	m_isPicked = FALSE;
	m_nDelay = 50;
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, TRUE);

	loop();

	m_nLevel = (m_nScore > 0) ? (m_nScore / 100 + 1) : 1;	// ���� �� �ֱ�
	m_rtBox1 = RECT_MAKE(m_ptPos1.x, m_ptPos1.y, 30);	// �÷��̾� RECT ����
	
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

	// ���ڿ��� ��ȯ�ϱ�
	_itoa_s(m_nLevel, szBuf, 10);
	std::string str = std::string(szBuf);
	str = "Level: " + str;
	TextOutA(hdc, 10, 10, str.c_str(), str.length());

	_itoa_s(m_nScore, szBuf, 10);
	str = std::string(szBuf);
	str = "����� ����: " + str;
	TextOutA(hdc, 10, 30, str.c_str(), str.length());

	_itoa_s(m_nTime, szBuf, 10);
	str = std::string(szBuf);
	str = "���� �ð�: " + str + "��";
	TextOutA(hdc, 10, 50, str.c_str(), str.length());

	_itoa_s(m_nHp, szBuf, 10);
	str = std::string(szBuf);
	str = "����� ü��: " + str;
	TextOutA(hdc, 10, 70, str.c_str(), str.length());

	EndPaint(g_hWnd, &ps);
}

void MainGame::Start()
{

}

void MainGame::Exit()
{

}