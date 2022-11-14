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
	POINT m_ptPos1;	// 플레이어의 RECT
	RECT m_rtBox1;	// 똥의 RECT
	float m_fMoveSpeed;
	int m_nScore;
	int m_nLevel;

	POINT m_ptMouse_prev;
	BOOL m_isPicked;

	std::vector<tagBox> m_vecBox;	// 똥의 rect 정보
	int m_nDelay;

public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};
