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
	POINT       m_ptPos1;				// ������ ��Ʈ�� ��ǥ ��
	RECT        m_rtBox1;               // �����ϴ� ��Ʈ ����
	float       m_fMoveSpeed;
	int         m_nScore;
	int         m_nLevel;

	POINT       m_ptMouse_prev;
	bool        m_isPicked;

	std::vector<tagBox>	m_vecBox;       // �������� ��Ʈ�� ����
	int					m_nDelay;


public:
	MainNode();
	~MainNode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};
