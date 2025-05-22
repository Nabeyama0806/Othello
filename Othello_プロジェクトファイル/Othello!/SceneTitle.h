#pragma once
#include "SceneBase.h"
#include "Node.h"

class Node;

//�^�C�g���V�[��
class SceneTitle : public SceneBase
{
public:
	enum class Mode
	{
		Solo,	//1�l�v���C
		Multi,	//2�l�v���C
		Watch,  //�ϐ� (CPU vs CPU)

		Select,	//�I��
	};

private:
	Node* m_rootNode;
	Mode m_mode;
	int m_bgm;

public:
	//�R���X�g���N�^
	SceneTitle() :
		m_mode(SceneTitle::Mode::Select),
		m_bgm(0),
		m_rootNode(nullptr){}

	virtual void Initialize() override;				//������
	virtual void Finalize() override;				//�I��
	virtual SceneBase* Update() override;			//�X�V
	virtual void Draw() override;					//�`��

	//���[�h�I��
	void SoloMode()
	{
		m_mode = Mode::Solo;
	}
	void MultiMode()
	{
		m_mode = Mode::Multi;
	}
	void WatchMode()
	{
		m_mode = Mode::Watch;
	}
};