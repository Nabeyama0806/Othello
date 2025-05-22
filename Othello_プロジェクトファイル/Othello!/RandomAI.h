#pragma once
#include "PlayerBase.h"

class RandomAI : public PlayerBase
{
private:
	static constexpr float WaitingTime = 1.2f;	//�ҋ@����

	float m_elapsedTime;	//�o�ߎ���

public:
	//�R���X�g���N�^
	RandomAI(Stone::Color color, Stage* stage) :
		PlayerBase(color, stage),
		m_elapsedTime(0)
	{
	}

	//�΂̐ݒu
	bool Play();
};