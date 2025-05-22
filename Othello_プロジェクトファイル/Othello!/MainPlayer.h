#pragma once
#include "PlayerBase.h"
#include "Stone.h"
#include "Stage.h"

class MainPlayer : public PlayerBase
{
public:
	//�R���X�g���N�^
	MainPlayer(Stone::Color color, Stage* stage) :
		PlayerBase(color, stage)
	{
	}

	//�΂̐ݒu
	bool Play();
};