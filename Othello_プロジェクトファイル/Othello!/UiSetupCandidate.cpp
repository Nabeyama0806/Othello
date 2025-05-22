#include "UiSetupCandidate.h"
#include "UiSetupStone.h"
#include <vector>

void UiSetupCandidate::Setup(Stone::Color color)
{
	//�q�I�u�W�F�N�g�̃m�[�h�𐶐�
	m_children = new Node();
	AddChild(m_children);

	//�ݒu�\�}�X���擾
	std::vector<Vector2> putList = m_stageNode->CheckPutStone(color);
	for (Vector2 pos : putList)
	{
		//���X�g�̐擪�v�f�̍��W�ɕ\�����Đ擪�v�f���폜
		m_children->AddChild(new UiSetupStone(m_stageNode->BoardToScreen(pos)));
	}
}