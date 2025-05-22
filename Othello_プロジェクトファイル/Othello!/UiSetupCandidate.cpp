#include "UiSetupCandidate.h"
#include "UiSetupStone.h"
#include <vector>

void UiSetupCandidate::Setup(Stone::Color color)
{
	//子オブジェクトのノードを生成
	m_children = new Node();
	AddChild(m_children);

	//設置可能マスを取得
	std::vector<Vector2> putList = m_stageNode->CheckPutStone(color);
	for (Vector2 pos : putList)
	{
		//リストの先頭要素の座標に表示して先頭要素を削除
		m_children->AddChild(new UiSetupStone(m_stageNode->BoardToScreen(pos)));
	}
}