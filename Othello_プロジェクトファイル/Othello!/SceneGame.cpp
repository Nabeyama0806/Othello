#include "SceneGame.h"
#include "SceneTitle.h"
#include "Screen.h"
#include "Input.h"
#include "Time.h"
#include "Node.h"
#include "Actor.h"
#include "ImageLoader.h"
#include "MainPlayer.h"
#include "RandomAI.h"
#include "Stage.h"
#include "Stone.h"
#include "UiSetupCandidate.h"
#include "UiStoneCount.h"
#include "PassEffect.h"

//������
void SceneGame::Initialize()
{
	//�摜�̎��O�ǂݍ���
	for (auto image : ImagePreload)
	{
		ImageLoader::GetInstance()->Load(image);
	}

	//���[�g
	m_rootNode = new Node();

	//�w�i
	m_rootNode->AddChild(new Actor("Background", "background.png", Screen::Center));

	//�A�N�^�[���C���[
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	//�Ֆ�
	m_stage = new Stage();
	actorLayer->AddChild(m_stage);

	//�ݒu�\�}�X�̕\��
	m_uiSetupCandidate = new UiSetupCandidate(m_stage);
	actorLayer->AddChild(m_uiSetupCandidate);
	m_uiSetupCandidate->Setup(m_turn);
	
	//�΂̐��̕\��
	m_uiStoneCount[0] = new UiStoneCount(Screen::CenterLeft + Vector2(106,92));
	m_uiStoneCount[1] = new UiStoneCount(Screen::CenterRight + Vector2(-28,  92));
	actorLayer->AddChild(m_uiStoneCount[0]);
	actorLayer->AddChild(m_uiStoneCount[1]);

	//�v���C���[
	m_player[0]->GetStageNode(m_stage);
	m_player[1]->GetStageNode(m_stage);
	m_player[static_cast<int>(m_turn)]->TurnStart();

	//BGM
	m_bgm = LoadSoundMem("Resource/sound/bgm_game.mp3");
	ChangeVolumeSoundMem(200, m_bgm);
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

//�I��
void SceneGame::Finalize()
{
	//���O�ǂݍ��݂����摜�̔j��
	for (auto image : ImagePreload)
	{
		ImageLoader::GetInstance()->Delete(image);
	}

	//�v���C���[�̍폜
	delete m_player[0];
	delete m_player[1];
	m_player[0] = nullptr;
	m_player[1] = nullptr;

	//�T�E���h�̍폜
	DeleteSoundMem(m_bgm);

	//�m�[�h�̍폜 
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

//�X�V
SceneBase* SceneGame::Update()
{
	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();

	switch (m_phase)
	{
	case Phase::Player:		//�v���C���[
		if (!m_player[static_cast<int>(m_turn)]->Play())
		{
			m_phase = Phase::ChangeTurn;
		}

		//�΂̐���\��
		m_uiStoneCount[0]->SetStoneCount(m_stage->StoneCount(Stone::Color::Black));
		m_uiStoneCount[1]->SetStoneCount(m_stage->StoneCount(Stone::Color::White));
		break;

	case Phase::ChangeTurn:	//���
		m_turn = m_turn == Stone::Color::Black ? Stone::Color::White : Stone::Color::Black;
		
		//�ݒu�\�}�X�̍X�V
		m_uiSetupCandidate->UnhideSetupCandidate();
		m_uiSetupCandidate->Setup(m_turn);

		//�ݒu�\�}�X��1���Ȃ���΃p�X
		if (m_player[static_cast<int>(m_turn)]->TurnStart())
		{
			//���̃^�[��
			if (m_passCount == 1) m_rootNode->AddChild(new PassEffect());
			m_passCount = 0;
			m_phase = Phase::Player;
		}
		else
		{
			//2��A���Ńp�X�ɂȂ�ƃQ�[���I��
			m_phase = Phase::Pass;
		}		
		break;

	case Phase::Pass:
		m_passCount++;
		m_phase = m_passCount == 2 ? Phase::Finish : Phase::ChangeTurn;
		break;

	case Phase::Finish:		//�Q�[���I��
		if (!m_isFinish)
		{
			m_isFinish = true;
			m_rootNode->AddChild(new Actor("Finish", "finish.png", Screen::Center));
		}

		m_gameLoopTime -= Time::GetInstance()->GetDeltaTime();
		if (m_gameLoopTime > 0) break;

		if (Input::GetInstance()->IsAnyKeyDown())
		{
			//�^�C�g���V�[���ɖ߂�
			return new SceneTitle();
		}
		break;
	}

	return this;
}

//�`��
void SceneGame::Draw()
{
	//�m�[�h�̕`��
	m_rootNode->TreeDraw();
}