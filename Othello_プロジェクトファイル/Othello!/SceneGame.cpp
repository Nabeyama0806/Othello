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

//初期化
void SceneGame::Initialize()
{
	//画像の事前読み込み
	for (auto image : ImagePreload)
	{
		ImageLoader::GetInstance()->Load(image);
	}

	//ルート
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor("Background", "background.png", Screen::Center));

	//アクターレイヤー
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	//盤面
	m_stage = new Stage();
	actorLayer->AddChild(m_stage);

	//設置可能マスの表示
	m_uiSetupCandidate = new UiSetupCandidate(m_stage);
	actorLayer->AddChild(m_uiSetupCandidate);
	m_uiSetupCandidate->Setup(m_turn);
	
	//石の数の表示
	m_uiStoneCount[0] = new UiStoneCount(Screen::CenterLeft + Vector2(106,92));
	m_uiStoneCount[1] = new UiStoneCount(Screen::CenterRight + Vector2(-28,  92));
	actorLayer->AddChild(m_uiStoneCount[0]);
	actorLayer->AddChild(m_uiStoneCount[1]);

	//プレイヤー
	m_player[0]->GetStageNode(m_stage);
	m_player[1]->GetStageNode(m_stage);
	m_player[static_cast<int>(m_turn)]->TurnStart();

	//BGM
	m_bgm = LoadSoundMem("Resource/sound/bgm_game.mp3");
	ChangeVolumeSoundMem(200, m_bgm);
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

//終了
void SceneGame::Finalize()
{
	//事前読み込みした画像の破棄
	for (auto image : ImagePreload)
	{
		ImageLoader::GetInstance()->Delete(image);
	}

	//プレイヤーの削除
	delete m_player[0];
	delete m_player[1];
	m_player[0] = nullptr;
	m_player[1] = nullptr;

	//サウンドの削除
	DeleteSoundMem(m_bgm);

	//ノードの削除 
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

//更新
SceneBase* SceneGame::Update()
{
	//ノードの更新
	m_rootNode->TreeUpdate();

	switch (m_phase)
	{
	case Phase::Player:		//プレイヤー
		if (!m_player[static_cast<int>(m_turn)]->Play())
		{
			m_phase = Phase::ChangeTurn;
		}

		//石の数を表示
		m_uiStoneCount[0]->SetStoneCount(m_stage->StoneCount(Stone::Color::Black));
		m_uiStoneCount[1]->SetStoneCount(m_stage->StoneCount(Stone::Color::White));
		break;

	case Phase::ChangeTurn:	//交代
		m_turn = m_turn == Stone::Color::Black ? Stone::Color::White : Stone::Color::Black;
		
		//設置可能マスの更新
		m_uiSetupCandidate->UnhideSetupCandidate();
		m_uiSetupCandidate->Setup(m_turn);

		//設置可能マスが1つもなければパス
		if (m_player[static_cast<int>(m_turn)]->TurnStart())
		{
			//次のターン
			if (m_passCount == 1) m_rootNode->AddChild(new PassEffect());
			m_passCount = 0;
			m_phase = Phase::Player;
		}
		else
		{
			//2回連続でパスになるとゲーム終了
			m_phase = Phase::Pass;
		}		
		break;

	case Phase::Pass:
		m_passCount++;
		m_phase = m_passCount == 2 ? Phase::Finish : Phase::ChangeTurn;
		break;

	case Phase::Finish:		//ゲーム終了
		if (!m_isFinish)
		{
			m_isFinish = true;
			m_rootNode->AddChild(new Actor("Finish", "finish.png", Screen::Center));
		}

		m_gameLoopTime -= Time::GetInstance()->GetDeltaTime();
		if (m_gameLoopTime > 0) break;

		if (Input::GetInstance()->IsAnyKeyDown())
		{
			//タイトルシーンに戻る
			return new SceneTitle();
		}
		break;
	}

	return this;
}

//描画
void SceneGame::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();
}