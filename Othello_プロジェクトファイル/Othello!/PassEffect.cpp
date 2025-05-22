#include "PassEffect.h"
#include "Time.h"

//コンストラクタ
PassEffect::PassEffect() :
	Actor("PassEffect", "pass.png", Screen::Center),
	m_elapsedTime(0) 
{
}

//更新
void PassEffect::Draw()
{
	//経過時間
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= DrawTime) Destroy();

	Actor::Draw();
}