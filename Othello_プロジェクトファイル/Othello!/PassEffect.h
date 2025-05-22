#pragma once
#include "Screen.h"
#include "Actor.h"
#include "Vector2.h"

class PassEffect : public Actor
{
private:
	static constexpr float DrawTime = 0.7f;
	
	float m_elapsedTime;

public:
	//コンストラクタ
	PassEffect();

	//更新
	void Draw();
};