#pragma once
#include "Node.h"
#include "Transform.h"

class UiStoneCount : public Node
{
private:
	static constexpr Vector2 FontSize = Vector2(20, 35);	//����1�����̕��E����
	static constexpr int FontMargin = 5;					//�����Ɛ����̊Ԃ̗]��

	int m_fontTextureId;		//�����t�H���g
	Transform m_transform;		//�p��
	int m_stoneCount;			//�X�R�A�̒l
	int m_drawStoneCount;		//�`��p�̃X�R�A
	int m_se;					//�X�R�A�㏸����SE

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	//�R���X�g���N�^
	UiStoneCount(Vector2 drawPos);

	//�΂̐����v�Z
	void SetStoneCount(int count);

	//�΂̐����擾
	int GetStoneCount() const
	{
		return m_stoneCount;
	}
};