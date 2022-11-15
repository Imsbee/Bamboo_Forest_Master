#pragma once
#include "framework.h"

class GameNode
{
public:
	GameNode();
	~GameNode();

	virtual void Start() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};