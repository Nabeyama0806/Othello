#include "RandomAI.h"
#include "Time.h"
#include "input.h"
#include "DxLib.h"

//�΂̐ݒu
bool RandomAI::Play()
{
	//�o�ߎ��Ԃ̉��Z
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= WaitingTime)
	{
		//�o�ߎ��Ԃ̃��Z�b�g
		m_elapsedTime = 0;

		//�ݒu�\���X�g�̗v�f�ԍ��������_���Ŏ擾
		int randomIndex = GetRand(static_cast<int>(m_putCandidate.size()) - 1);

		//�΂�ݒu
		m_stageNode->PutStone(m_putCandidate[randomIndex], m_color);

		//�^�[���I��
		return false;
	}

	//�܂��΂�ݒu���Ă��Ȃ��̂Ń^�[�����s
	return true;
}