#include "MainPlayer.h"
#include "Input.h"
#include "DxLib.h"

//石の設置
bool MainPlayer::Play()
{
	//左クリックが押されたか
	if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_LEFT))
	{
		//マウスのクリックされた座標をマス目に変換
		Vector2 position = Stage::ScreenToBoard(Input::GetInstance()->GetMousePoint());

		//指定されたマス目に何もなく、設置可能マスに含まれているか
		if (m_stageNode->IsEmpty(position)
		&& std::find(m_putCandidate.begin(), m_putCandidate.end(), position) != m_putCandidate.end())
		{
			//何もなければ設置
			m_stageNode->PutStone(position, m_color);

			//ターン終了
			return false;
		}
	}

	//まだ石を設置していないのでターン続行
	return true;
}