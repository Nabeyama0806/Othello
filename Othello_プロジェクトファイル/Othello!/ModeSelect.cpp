#include "ModeSelect.h"
#include "SceneGame.h"
#include "DxLib.h"

//�R���X�g���N�^
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

//�X�V
void ModeSelect::Update()
{
	//�{���̏���
	Actor::Update();

	//�{�^��
	m_button.Update(m_transform.position);
}

//�`��
void ModeSelect::Draw()
{
	//�{���̏���
	Actor::Draw();


#ifdef _DEBUG
	m_button.Draw(m_transform.position);
#endif
}