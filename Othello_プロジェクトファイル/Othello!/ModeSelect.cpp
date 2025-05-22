#include "ModeSelect.h"
#include "SceneGame.h"
#include "DxLib.h"

//コンストラクタ
ModeSelect::ModeSelect(
	SceneTitle* sceneTitle,
	SceneTitle::Mode mode,
	const Vector2& position,
	const char* textureName,
	std::function<void()> callbackFunction
) :
	Actor("ModeSelect", textureName, position),
	m_sceneTitleNode(sceneTitle),
	m_mode(mode),
	m_button(Size, MOUSE_INPUT_LEFT, callbackFunction)
{
}

//更新
void ModeSelect::Update()
{
	//本来の処理
	Actor::Update();

	//ボタン
	m_button.Update(m_transform.position);
}

//描画
void ModeSelect::Draw()
{
	//本来の処理
	Actor::Draw();


#ifdef _DEBUG
	m_button.Draw(m_transform.position);
#endif
}