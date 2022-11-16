#pragma once

class GameNode
{
public:
	GameNode();
	~GameNode();

	virtual void Init() = 0; // 순수 가상 함수
	virtual void Update() = 0;
	virtual void Render() = 0;

};