#pragma once
#include"SceneBase.h"
#include "Stone.h"
#include <list>

//前方宣言
class Node;
class Stage;
class PlayerBase;
class UiSetupCandidate;
class UiStoneCount;

//ゲームシーン
class SceneGame : public SceneBase
{
private:
	static constexpr float WaitTime = 0.8f;

	const std::list<const char*> ImagePreload =
	{
		"flipbox.png",
		"setup_stone.png"
	};

	enum class Phase
	{
		Player,
		ChangeTurn,
		Pass,
		Wait,
		Finish,
	};

	Phase m_phase;
	Node* m_rootNode;
	Stage* m_stage;
	UiSetupCandidate* m_uiSetupCandidate;
	UiStoneCount* m_uiStoneCount[2];
	PlayerBase* m_player[2];

	Stone::Color m_turn;
	Phase m_nextPhase;
	float m_elapsedTime;
	float m_duration;
	float m_gameLoopTime;
	int m_passCount;
	int m_bgm;

	bool m_isFinish;

public:
	//コンストラクタ
	SceneGame(PlayerBase* player1, PlayerBase* player2) :
		m_phase(Phase::Player),
		m_rootNode(nullptr),
		m_stage(nullptr),
		m_uiSetupCandidate(nullptr),
		m_player{ nullptr },
		m_turn(Stone::Color::Black),
		m_elapsedTime(0),
		m_duration(0),
		m_gameLoopTime(1.5f),
		m_passCount(0),
		m_nextPhase(m_phase),
		m_isFinish(false) 
	{
		m_player[0] = player1;
		m_player[1] = player2;
	}

	virtual void Initialize() override;		//初期化
	virtual void Finalize() override;		//終了
	virtual SceneBase* Update() override;	//更新
	virtual void Draw() override;			//描画
};