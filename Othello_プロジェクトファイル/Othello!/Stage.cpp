#include "Screen.h"
#include "Stage.h"
#include "Stone.h"

//コンストラクタ
Stage::Stage() :
	m_board{ nullptr }
{
	//初期石
	PutStone(Vector2(3, 3), Stone::Color::White);
	PutStone(Vector2(3, 4), Stone::Color::Black);
	PutStone(Vector2(4, 3), Stone::Color::Black);
	PutStone(Vector2(4, 4), Stone::Color::White);
}						  

//反転可能な石の列挙
void Stage::CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList)
{
	//走査
	for (int dir = 0; dir < Direction; ++dir)
	{
		//反転できるか確認
		_CheckFlip(boardPos + Dir[dir], color, flipList, dir);
	}
}

//反転可能な石の列挙 (再帰関数)
bool Stage::_CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList, int dir)
{
	//盤面内か確認
	if (!IsInsideBoard(boardPos)) return false;

	//指定されたマスの石を保持する
	Stone* stone = m_board[static_cast<int>(boardPos.x)][static_cast<int>(boardPos.y)];

	//指定されたマスに石があるか確認
	if (!stone) return false;

	//指定されたマスの色を確認
	if (stone->GetColor() == color) return true;

	//dirの方向を探索
	if (_CheckFlip(boardPos + Dir[dir], color, flipList, dir))
	{
		flipList->push_back(stone);
		return true;
	}

	//反転させる石がないのでfalseを返して終了
	return false;
}

//石を盤面に設置する
void Stage::PutStone(const Vector2& boardPos, Stone::Color color)
{
	//指定されたマスの石を取得
	Stone* stone = new Stone(boardPos, color);
	AddChild(stone);

	//盤面に設置
	m_board[static_cast<int>(boardPos.x)][static_cast<int>(boardPos.y)] = stone;

	//反転させる石があるか確認
	std::list<Stone*> flipList;
	CheckFlip(stone->GetBoardPos(), stone->GetColor(), &flipList);
	for (auto stone : flipList)
	{
		//リストに登録した石を反転させる
		stone->Flip();
	}
}

//石を設置できるマスがあるか
std::vector<Vector2> Stage::CheckPutStone(Stone::Color color)
{
	//設置可能マスリスト
	std::vector<Vector2> putList;
	
	//盤面の全てのマスを走査
	for (int y = 0; y < Row; ++y)
	{
		for(int x = 0; x < Column; ++x)
		{
			//既に石が置かれているか
			if (!IsEmpty(Vector2(x, y))) continue;

			//設置可能か調べる
			std::list<Stone*> flipList;
			CheckFlip(Vector2(x, y), color, &flipList);
			if (!flipList.empty())
			{	
				//設置可能リストに追加
				putList.push_back(Vector2(x, y));
			}
		}
	}
	
	return putList;
}

//同じ色の石を数える
int Stage::StoneCount(Stone::Color color)
{
	int sameColorCount = 0;

	//盤面の全てのマスを走査
	for (int y = 0; y < Row; ++y)
	{
		for (int x = 0; x < Column; ++x)
		{
			//既に石が置かれているか
			if (!m_board[x][y]) continue;

			//現在のマスにある石の色が自分の色と同じか
			if (m_board[x][y]->GetColor() != color) continue;

			//同じ色の石があれば加算
			sameColorCount++;
		}
	}

	return sameColorCount;
}

//指定したマスが空いているか
bool Stage::IsEmpty(const Vector2& boardPos)
{
	//盤面外を指定されたら空いていないことにする
	if (!IsInsideBoard(boardPos)) return false;
	
	return !m_board[static_cast<int>(boardPos.x)][static_cast<int>(boardPos.y)];
}

//盤面内を指定しているか
bool Stage::IsInsideBoard(const Vector2& boardPos)
{
	//盤面外
	if (boardPos.x < 0 || boardPos.x >= Column) return false;
	if (boardPos.y < 0 || boardPos.y >= Row)	return false;

	return true;
}

//マス目から描画座標への変換
const Vector2 Stage::BoardToScreen(const Vector2& boardPos)
{
	 return TopLeft + Stone::Size / 2 + Vector2(boardPos.x * Stone::Size.x, boardPos.y * Stone::Size.y);
}

//描画座標からマス目への変換
const Vector2 Stage::ScreenToBoard(const Vector2& screenPos)
{
	Vector2 tmp = screenPos - TopLeft;
	if (tmp.x <= 0 || tmp.y <= 0) return -tmp;
	return Vector2(static_cast<int>(tmp.x / Stone::Size.x), static_cast<int>(tmp.y / Stone::Size.y));
}