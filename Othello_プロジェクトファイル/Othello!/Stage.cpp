#include "Screen.h"
#include "Stage.h"
#include "Stone.h"

//�R���X�g���N�^
Stage::Stage() :
	m_board{ nullptr }
{
	//������
	PutStone(Vector2(3, 3), Stone::Color::White);
	PutStone(Vector2(3, 4), Stone::Color::Black);
	PutStone(Vector2(4, 3), Stone::Color::Black);
	PutStone(Vector2(4, 4), Stone::Color::White);
}						  

//���]�\�Ȑ΂̗�
void Stage::CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList)
{
	//����
	for (int dir = 0; dir < Direction; ++dir)
	{
		//���]�ł��邩�m�F
		_CheckFlip(boardPos + Dir[dir], color, flipList, dir);
	}
}

//���]�\�Ȑ΂̗� (�ċA�֐�)
bool Stage::_CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList, int dir)
{
	//�Ֆʓ����m�F
	if (!IsInsideBoard(boardPos)) return false;

	//�w�肳�ꂽ�}�X�̐΂�ێ�����
	Stone* stone = m_board[static_cast<int>(boardPos.x)][static_cast<int>(boardPos.y)];

	//�w�肳�ꂽ�}�X�ɐ΂����邩�m�F
	if (!stone) return false;

	//�w�肳�ꂽ�}�X�̐F���m�F
	if (stone->GetColor() == color) return true;

	//dir�̕�����T��
	if (_CheckFlip(boardPos + Dir[dir], color, flipList, dir))
	{
		flipList->push_back(stone);
		return true;
	}

	//���]������΂��Ȃ��̂�false��Ԃ��ďI��
	return false;
}

//�΂�Ֆʂɐݒu����
void Stage::PutStone(const Vector2& boardPos, Stone::Color color)
{
	//�w�肳�ꂽ�}�X�̐΂��擾
	Stone* stone = new Stone(boardPos, color);
	AddChild(stone);

	//�Ֆʂɐݒu
	m_board[static_cast<int>(boardPos.x)][static_cast<int>(boardPos.y)] = stone;

	//���]������΂����邩�m�F
	std::list<Stone*> flipList;
	CheckFlip(stone->GetBoardPos(), stone->GetColor(), &flipList);
	for (auto stone : flipList)
	{
		//���X�g�ɓo�^�����΂𔽓]������
		stone->Flip();
	}
}

//�΂�ݒu�ł���}�X�����邩
std::vector<Vector2> Stage::CheckPutStone(Stone::Color color)
{
	//�ݒu�\�}�X���X�g
	std::vector<Vector2> putList;
	
	//�Ֆʂ̑S�Ẵ}�X�𑖍�
	for (int y = 0; y < Row; ++y)
	{
		for(int x = 0; x < Column; ++x)
		{
			//���ɐ΂��u����Ă��邩
			if (!IsEmpty(Vector2(x, y))) continue;

			//�ݒu�\�����ׂ�
			std::list<Stone*> flipList;
			CheckFlip(Vector2(x, y), color, &flipList);
			if (!flipList.empty())
			{	
				//�ݒu�\���X�g�ɒǉ�
				putList.push_back(Vector2(x, y));
			}
		}
	}
	
	return putList;
}

//�����F�̐΂𐔂���
int Stage::StoneCount(Stone::Color color)
{
	int sameColorCount = 0;

	//�Ֆʂ̑S�Ẵ}�X�𑖍�
	for (int y = 0; y < Row; ++y)
	{
		for (int x = 0; x < Column; ++x)
		{
			//���ɐ΂��u����Ă��邩
			if (!m_board[x][y]) continue;

			//���݂̃}�X�ɂ���΂̐F�������̐F�Ɠ�����
			if (m_board[x][y]->GetColor() != color) continue;

			//�����F�̐΂�����Ή��Z
			sameColorCount++;
		}
	}

	return sameColorCount;
}

//�w�肵���}�X���󂢂Ă��邩
bool Stage::IsEmpty(const Vector2& boardPos)
{
	//�ՖʊO���w�肳�ꂽ��󂢂Ă��Ȃ����Ƃɂ���
	if (!IsInsideBoard(boardPos)) return false;
	
	return !m_board[static_cast<int>(boardPos.x)][static_cast<int>(boardPos.y)];
}

//�Ֆʓ����w�肵�Ă��邩
bool Stage::IsInsideBoard(const Vector2& boardPos)
{
	//�ՖʊO
	if (boardPos.x < 0 || boardPos.x >= Column) return false;
	if (boardPos.y < 0 || boardPos.y >= Row)	return false;

	return true;
}

//�}�X�ڂ���`����W�ւ̕ϊ�
const Vector2 Stage::BoardToScreen(const Vector2& boardPos)
{
	 return TopLeft + Stone::Size / 2 + Vector2(boardPos.x * Stone::Size.x, boardPos.y * Stone::Size.y);
}

//�`����W����}�X�ڂւ̕ϊ�
const Vector2 Stage::ScreenToBoard(const Vector2& screenPos)
{
	Vector2 tmp = screenPos - TopLeft;
	if (tmp.x <= 0 || tmp.y <= 0) return -tmp;
	return Vector2(static_cast<int>(tmp.x / Stone::Size.x), static_cast<int>(tmp.y / Stone::Size.y));
}