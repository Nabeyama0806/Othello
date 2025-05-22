#pragma once
#include "PlayerBase.h"

class RandomAI : public PlayerBase
{
private:
	static constexpr float WaitingTime = 1.2f;	//待機時間

	float m_elapsedTime;	//経過時間

public:
	//コンストラクタ
	RandomAI(Stone::Color color, Stage* stage) :
		PlayerBase(color, stage),
		m_elapsedTime(0)
	{
	}

	//石の設置
	bool Play();
};