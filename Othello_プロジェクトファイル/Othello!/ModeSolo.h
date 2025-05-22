#pragma once
#include "ModeSelect.h"
#include "SceneTitle.h"

class ModeSolo : public ModeSelect
{
private:
	static constexpr Vector2 Position = Vector2(534, 205);

public:
	ModeSolo(SceneTitle* sceneTitleNode, SceneTitle::Mode mode) :
		ModeSelect(
			sceneTitleNode,
			mode,
			Position,
			"mode_solo.png",
			std::bind(&SceneTitle::SoloMode, sceneTitleNode)
		)
	{
	}
};