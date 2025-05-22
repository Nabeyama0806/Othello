#include "MainPlayer.h"
#include "Input.h"
#include "DxLib.h"

//�΂̐ݒu
bool MainPlayer::Play()
{
	//���N���b�N�������ꂽ��
	if (Input::GetInstance()->IsMouseDown(MOUSE_INPUT_LEFT))
	{
		//�}�E�X�̃N���b�N���ꂽ���W���}�X�ڂɕϊ�
		Vector2 position = Stage::ScreenToBoard(Input::GetInstance()->GetMousePoint());

		//�w�肳�ꂽ�}�X�ڂɉ����Ȃ��A�ݒu�\�}�X�Ɋ܂܂�Ă��邩
		if (m_stageNode->IsEmpty(position)
		&& std::find(m_putCandidate.begin(), m_putCandidate.end(), position) != m_putCandidate.end())
		{
			//�����Ȃ���ΐݒu
			m_stageNode->PutStone(position, m_color);

			//�^�[���I��
			return false;
		}
	}

	//�܂��΂�ݒu���Ă��Ȃ��̂Ń^�[�����s
	return true;
}