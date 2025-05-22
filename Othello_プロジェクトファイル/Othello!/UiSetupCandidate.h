#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Stage.h"
#include "Stone.h"

class UiSetupCandidate : public Node
{
private:
	Stage* m_stageNode;		//�X�e�[�W�̎擾
	Node* m_children;		//�q�I�u�W�F�N�g

public:
	//�R���X�g���N�^
	UiSetupCandidate(Stage* const stageNode) :
		m_stageNode(stageNode),
		m_children(nullptr) {}

	//�ݒu�\�}�X�̕\��
	void Setup(Stone::Color color);

	//�\���̃��Z�b�g
	void UnhideSetupCandidate()
	{
		//���g���܂߂��q�I�u�W�F�N�g�̃��Z�b�g
		RemoveChild(m_children);
		m_children = nullptr;
	}
};