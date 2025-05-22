#pragma once
#include "PlayerBase.h"
#include "Stone.h"
#include "Stage.h"

class MainPlayer : public PlayerBase
{
public:
	//コンストラクタ
	MainPlayer(Stone::Color color, Stage* stage) :
		PlayerBase(color, stage)
	{
	}

	//石の設置
	bool Play();
};