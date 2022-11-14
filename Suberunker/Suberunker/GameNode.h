#pragma once
#include "framework.h"

class GameNode
{
public:
	GameNode();
	~GameNode();

	// 순수 가상 함수
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
