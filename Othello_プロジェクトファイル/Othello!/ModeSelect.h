#pragma once
#include "Actor.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "Button.h"
#include "Vector2.h"

class ModeSelect : public Actor
{
private:
	static constexpr Vector2 Size = Vector2(169, 50);

protected:
	SceneTitle* m_sceneTitleNode;	//タイトルのノード
	SceneTitle::Mode m_mode;		//選択されたゲームモード
	Button m_button;

	virtual void Update() override;	//更新
	virtual void Draw() override;	//更新

public:
	//コンストラクタ
	ModeSelect(
		SceneTitle* sceneTitle,
		SceneTitle::Mode mode,
		const Vector2& position,
		const char* textureName,
		std::function<void()> callbackFunction
	);
};