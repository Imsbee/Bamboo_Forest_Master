#pragma once
#include "framework.h"

class GameNode
{
public:
	GameNode();
	~GameNode();

	// ���� ���� �Լ�
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
