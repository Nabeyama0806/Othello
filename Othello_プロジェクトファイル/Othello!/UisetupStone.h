#pragma once
#include "Actor.h"
#include "Vector2.h"
#include "Stone.h"

class UiSetupStone : public Actor
{
private:
	static constexpr Vector2 GridSize = Vector2(876, 865);
	static constexpr int GridNum = 7;
	static constexpr float SizeOffset = 0.045f;

	const char* AnimeName = "SetupStone";
	const Animation FlipBox = Animation("setup_stone.png", 1, 17);
public:
	//コンストラクタ
	UiSetupStone(Vector2 position);
};