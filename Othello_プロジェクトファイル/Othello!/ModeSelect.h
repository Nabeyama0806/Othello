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
	SceneTitle* m_sceneTitleNode;	//�^�C�g���̃m�[�h
	SceneTitle::Mode m_mode;		//�I�����ꂽ�Q�[�����[�h
	Button m_button;

	virtual void Update() override;	//�X�V
	virtual void Draw() override;	//�X�V

public:
	//�R���X�g���N�^
	ModeSelect(
		SceneTitle* sceneTitle,
		SceneTitle::Mode mode,
		const Vector2& position,
		const char* textureName,
		std::function<void()> callbackFunction
	);
};