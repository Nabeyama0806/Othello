#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Stage.h"
#include "Stone.h"

class UiSetupCandidate : public Node
{
private:
	Stage* m_stageNode;		//ステージの取得
	Node* m_children;		//子オブジェクト

public:
	//コンストラクタ
	UiSetupCandidate(Stage* const stageNode) :
		m_stageNode(stageNode),
		m_children(nullptr) {}

	//設置可能マスの表示
	void Setup(Stone::Color color);

	//表示のリセット
	void UnhideSetupCandidate()
	{
		//自身を含めた子オブジェクトのリセット
		RemoveChild(m_children);
		m_children = nullptr;
	}
};