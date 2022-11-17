#pragma once
#include "GameNode.h"

class MainNode : public GameNode
{
private:

	struct tagBox
	{
		RECT    rt;
		float   speed;
	};


private:
	POINT       m_ptPos1;				// 조작할 렉트의 좌표 값
	RECT        m_rtBox1;               // 조작하는 렉트 정보
	float       m_fMoveSpeed;
	int         m_nScore;
	int         m_nLevel;

	POINT       m_ptMouse_prev;
	bool        m_isPicked;

	std::vector<tagBox>	m_vecBox;       // 떨어지는 렉트의 정보
	int					m_nDelay;


public:
	MainNode();
	~MainNode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};
