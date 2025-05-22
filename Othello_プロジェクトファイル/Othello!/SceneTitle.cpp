#include "SceneTitle.h"
#include "SceneGame.h"
#include "ModeSolo.h"
#include "ModeMulti.h"
#include "ModeWatch.h"
#include "MainPlayer.h"
#include "RandomAI.h"
#include "DxLib.h"
#include "Input.h"
#include "Screen.h"
#include "Actor.h"
#include "Stone.h"

//������
void SceneTitle::Initialize()
{
	m_rootNode = new Node();

	//�w�i
	m_rootNode->AddChild(new Actor(
		"Background",
		"title.png",
		Screen::Center
	));

	//���[�h�I���{�^��
	m_rootNode->AddChild(new ModeSolo(this, Mode::Solo));
	m_rootNode->AddChild(new ModeMulti(this, Mode::Multi));
	m_rootNode->AddChild(new ModeWatch(this, Mode::Watch));

	//BGM
	m_bgm = LoadSoundMem("Resource/sound/bgm_title.mp3");
	ChangeVolumeSoundMem(220, m_bgm);
	PlaySoundMem(m_bgm, DX_PLAYTYPE_BACK);
}

//�I��
void SceneTitle::Finalize()
{
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;

	//�T�E���h�̍폜
	DeleteSoundMem(m_bgm);
}

//�X�V
SceneBase* SceneTitle::Update()
{
	switch (m_mode)
	{
	case Mode::Solo:
		return new SceneGame(new MainPlayer(Stone::Color::Black, nullptr), new RandomAI(Stone::Color::White, nullptr));
		break;

	case Mode::Multi:
		return new SceneGame(new MainPlayer(Stone::Color::Black, nullptr), new MainPlayer(Stone::Color::White, nullptr));
		break;

	case Mode::Watch:
		return new SceneGame(new RandomAI(Stone::Color::Black, nullptr), new RandomAI(Stone::Color::White, nullptr));
		break;		
	}

	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();

	return this;
}

//�`��
void SceneTitle::Draw()
{
	//�m�[�h�̕`��
	m_rootNode->TreeDraw();
}