#pragma once
#include "Stone.h"
#include "Stage.h"
#include "Vector2.h"
#include <vector>

class PlayerBase
{
protected:
	Stone::Color m_color;		//自身の色
	Stage* m_stageNode;			//SceneGame上のStageノード
	std::vector<Vector2> m_putCandidate;	//置けるマスのリスト

public:
	//コンストラクタ
	PlayerBase(Stone::Color color, Stage* stage);

	//置けるマスがあるか確認
	bool TurnStart();

	//生成したプレイヤーに盤面の情報を渡す
	void GetStageNode(Stage* stageNode)
	{
		m_stageNode = stageNode;
	}

	//石の設置
	virtual bool Play() = 0;
};