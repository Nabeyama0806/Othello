#include "UiSetupStone.h"

UiSetupStone::UiSetupStone(Vector2 position) :
	Actor("SetupStone", "setup_stone.png", position)
{
	//アニメーション
	m_sprite = new Sprite();
	m_sprite->Register(AnimeName, FlipBox);
	m_sprite->gridSize = GridSize;
	m_transform.scale = SizeOffset;
}