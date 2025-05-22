#include "Time.h"
#include "Input.h"
#include "DxLib.h"

//�R���X�g���N�^
Time::Time() :
	m_prevTime(GetNowCount()),
	m_deltaTime(0)
{
}

//�X�V
void Time::Update()
{
	int nowTime = GetNowCount();

	//�O�t���[���̎����ƌ��ݎ�������o�ߎ��Ԃ����߂�
	//�P�ʂ��~���b����b�ɕϊ�
	m_deltaTime = (nowTime - m_prevTime) / 1000.0f;

	//���ݎ������o���Ă���
	m_prevTime = nowTime;
}