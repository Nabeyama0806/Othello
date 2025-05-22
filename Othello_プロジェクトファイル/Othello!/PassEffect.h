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
	//�R���X�g���N�^
	PassEffect();

	//�X�V
	void Draw();
};