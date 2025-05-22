#pragma once
#include "Node.h"
#include "Stone.h"
#include <vector>

class Stage : public Node
{
private:
	static constexpr int Column = 8;		//横のマス(列)
	static constexpr int Row = 8;			//縦のマス(行)
	static constexpr int Direction = 8;		//探索する方向の数
	static constexpr int EraseCount = 1;	//石を消せる最小数
	static constexpr Vector2 TopLeft = Vector2(136, 56);		//盤面の左上座標

	//走査する方向
	static constexpr Vector2 Dir[] =
	{
		Vector2(-1,  0), //左
		Vector2(-1, -1), //左上
		Vector2( 0, -1), //真上
		Vector2( 1, -1), //右上
		Vector2( 1,  0), //右
		Vector2( 1,  1), //右下
		Vector2( 0,  1), //真下
		Vector2(-1,  1), //左下
	};

	//盤面
	Stone* m_board[Column][Row];

	//反転可能な石の列挙
	void CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList);
	bool _CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList, int dir);

public:
	//コンストラクタ
	Stage();

	//プレイヤーの操作が終了した石を盤面に設置する
	void PutStone(const Vector2& boardPos, Stone::Color color);

	//指定したマスに石を設置できるか
	std::vector<Vector2> CheckPutStone(Stone::Color color);

	//同じ色の石を数える
	int StoneCount(Stone::Color color);

	//指定したマスが空いているか
	bool IsEmpty(const Vector2& boardPos);

	//盤面内を指定しているか
	bool IsInsideBoard(const Vector2& boardPos);

	//マス目から描画座標への変換
	static const Vector2 BoardToScreen(const Vector2& boardPos);

	//描画座標からマス目への変換
	static const Vector2 ScreenToBoard(const Vector2& screenPos);
};