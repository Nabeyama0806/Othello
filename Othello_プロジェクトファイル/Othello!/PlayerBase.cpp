#include "PlayerBase.h"

//�R���X�g���N�^
PlayerBase::PlayerBase(Stone::Color color, Stage* stage) :
	m_color(color),
	m_stageNode(stage)
{

}

//�u����}�X�����邩�m�F
bool PlayerBase::TurnStart()
{
	m_putCandidate = m_stageNode->CheckPutStone(m_color);
	if (m_putCandidate.empty()) return false;

	return true;
}