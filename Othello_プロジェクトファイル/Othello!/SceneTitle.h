#pragma once
#include "SceneBase.h"
#include "Node.h"

class Node;

//タイトルシーン
class SceneTitle : public SceneBase
{
public:
	enum class Mode
	{
		Solo,	//1人プレイ
		Multi,	//2人プレイ
		Watch,  //観戦 (CPU vs CPU)

		Select,	//選択中
	};

private:
	Node* m_rootNode;
	Mode m_mode;
	int m_bgm;

public:
	//コンストラクタ
	SceneTitle() :
		m_mode(SceneTitle::Mode::Select),
		m_bgm(0),
		m_rootNode(nullptr){}

	virtual void Initialize() override;				//初期化
	virtual void Finalize() override;				//終了
	virtual SceneBase* Update() override;			//更新
	virtual void Draw() override;					//描画

	//モード選択
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