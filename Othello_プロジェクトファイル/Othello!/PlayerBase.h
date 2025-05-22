#pragma once
#include "Stone.h"
#include "Stage.h"
#include "Vector2.h"
#include <vector>

class PlayerBase
{
protected:
	Stone::Color m_color;		//���g�̐F
	Stage* m_stageNode;			//SceneGame���Stage�m�[�h
	std::vector<Vector2> m_putCandidate;	//�u����}�X�̃��X�g

public:
	//�R���X�g���N�^
	PlayerBase(Stone::Color color, Stage* stage);

	//�u����}�X�����邩�m�F
	bool TurnStart();

	//���������v���C���[�ɔՖʂ̏���n��
	void GetStageNode(Stage* stageNode)
	{
		m_stageNode = stageNode;
	}

	//�΂̐ݒu
	virtual bool Play() = 0;
};