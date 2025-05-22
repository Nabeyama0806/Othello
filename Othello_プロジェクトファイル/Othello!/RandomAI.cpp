#include "RandomAI.h"
#include "Time.h"
#include "input.h"
#include "DxLib.h"

//石の設置
bool RandomAI::Play()
{
	//経過時間の加算
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= WaitingTime)
	{
		//経過時間のリセット
		m_elapsedTime = 0;

		//設置可能リストの要素番号をランダムで取得
		int randomIndex = GetRand(static_cast<int>(m_putCandidate.size()) - 1);

		//石を設置
		m_stageNode->PutStone(m_putCandidate[randomIndex], m_color);

		//ターン終了
		return false;
	}

	//まだ石を設置していないのでターン続行
	return true;
}