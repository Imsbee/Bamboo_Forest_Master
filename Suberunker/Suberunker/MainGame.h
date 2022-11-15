#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	struct tagBox
	{
		RECT rt;
		float speed;
	};

private:
	POINT m_ptPos1;		// �÷��̾��� ��ǥ
	RECT	m_rtBox1;		// �÷��̾��� RECT
	float	m_fMoveSpeed;
	int		m_nScore;
	int		m_nLevel;
	int		m_nHp;
	int		m_nTime;

	POINT	m_ptMouse_prev;	// ���콺�� ��ǥ
	BOOL	m_isPicked;				

	std::vector<tagBox> m_vecBox;	// ��
	int								 m_nDelay;

public:
	MainGame();
	~MainGame();

	virtual void Start() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Exit() override;

	// �÷��̾��� ������ ����
	void loop()
	{
		D2D1_POINT_2F offset = { 0, 0 };

		if (KeyBuffer[VK_LEFT] == KeyBuffer[VK_RIGHT])
			offset.x = 0.f;
		else if (KeyBuffer[VK_LEFT])
		{
			if (m_ptPos1.x > 0)
				offset.x = -10.f;
		}
		else
		{
			if (m_ptPos1.x < windows_size_width - 50)
				offset.x = 10.f;
		}

		m_ptPos1.x += offset.x;
	}
};

