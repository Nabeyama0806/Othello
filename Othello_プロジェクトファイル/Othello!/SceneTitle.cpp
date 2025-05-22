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

//初期化
void SceneTitle::Initialize()
{
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor(
		"Background",
		"title.png",
		Screen::Center
	));

	//モード選択ボタン
	m_rootNode->AddChild(new ModeSolo(this, Mode::Solo));
	m_rootNode->AddChild(new ModeMulti(this, Mode::Multi));
	m_rootNode->AddChild(new ModeWatch(this, Mode::Watch));

	//BGM
	m_bgm = LoadSoundMem("Resource/sound/bgm_title.mp3");
	ChangeVolumeSoundMem(220, m_bgm);
	PlaySoundMem(m_bgm, DX_PLAYTYPE_BACK);
}

//終了
void SceneTitle::Finalize()
{
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;

	//サウンドの削除
	DeleteSoundMem(m_bgm);
}

//更新
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

	//ノードの更新
	m_rootNode->TreeUpdate();

	return this;
}

//描画
void SceneTitle::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();
}