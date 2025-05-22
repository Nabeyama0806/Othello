#pragma once
#include "Node.h"
#include "Stone.h"
#include <vector>

class Stage : public Node
{
private:
	static constexpr int Column = 8;		//���̃}�X(��)
	static constexpr int Row = 8;			//�c�̃}�X(�s)
	static constexpr int Direction = 8;		//�T����������̐�
	static constexpr int EraseCount = 1;	//�΂�������ŏ���
	static constexpr Vector2 TopLeft = Vector2(136, 56);		//�Ֆʂ̍�����W

	//�����������
	static constexpr Vector2 Dir[] =
	{
		Vector2(-1,  0), //��
		Vector2(-1, -1), //����
		Vector2( 0, -1), //�^��
		Vector2( 1, -1), //�E��
		Vector2( 1,  0), //�E
		Vector2( 1,  1), //�E��
		Vector2( 0,  1), //�^��
		Vector2(-1,  1), //����
	};

	//�Ֆ�
	Stone* m_board[Column][Row];

	//���]�\�Ȑ΂̗�
	void CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList);
	bool _CheckFlip(const Vector2& boardPos, Stone::Color color, std::list<Stone*>* flipList, int dir);

public:
	//�R���X�g���N�^
	Stage();

	//�v���C���[�̑��삪�I�������΂�Ֆʂɐݒu����
	void PutStone(const Vector2& boardPos, Stone::Color color);

	//�w�肵���}�X�ɐ΂�ݒu�ł��邩
	std::vector<Vector2> CheckPutStone(Stone::Color color);

	//�����F�̐΂𐔂���
	int StoneCount(Stone::Color color);

	//�w�肵���}�X���󂢂Ă��邩
	bool IsEmpty(const Vector2& boardPos);

	//�Ֆʓ����w�肵�Ă��邩
	bool IsInsideBoard(const Vector2& boardPos);

	//�}�X�ڂ���`����W�ւ̕ϊ�
	static const Vector2 BoardToScreen(const Vector2& boardPos);

	//�`����W����}�X�ڂւ̕ϊ�
	static const Vector2 ScreenToBoard(const Vector2& screenPos);
};