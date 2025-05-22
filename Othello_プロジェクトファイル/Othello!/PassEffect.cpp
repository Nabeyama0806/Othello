#include "PassEffect.h"
#include "Time.h"

//�R���X�g���N�^
PassEffect::PassEffect() :
	Actor("PassEffect", "pass.png", Screen::Center),
	m_elapsedTime(0) 
{
}

//�X�V
void PassEffect::Draw()
{
	//�o�ߎ���
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= DrawTime) Destroy();

	Actor::Draw();
}