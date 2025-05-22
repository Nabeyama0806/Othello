#include "PlayerBase.h"

//コンストラクタ
PlayerBase::PlayerBase(Stone::Color color, Stage* stage) :
	m_color(color),
	m_stageNode(stage)
{

}

//置けるマスがあるか確認
bool PlayerBase::TurnStart()
{
	m_putCandidate = m_stageNode->CheckPutStone(m_color);
	if (m_putCandidate.empty()) return false;

	return true;
}