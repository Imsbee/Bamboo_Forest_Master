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
	POINT m_ptPos1;	// �÷��̾��� RECT
	RECT m_rtBox1;	// ���� RECT
	float m_fMoveSpeed;
	int m_nScore;
	int m_nLevel;

	POINT m_ptMouse_prev;
	BOOL m_isPicked;

	std::vector<tagBox> m_vecBox;	// ���� rect ����
	int m_nDelay;

public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};
