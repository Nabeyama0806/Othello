#pragma once
#include "ModeSelect.h"
#include "SceneTitle.h"

class ModeMulti : public ModeSelect
{
private:
	static constexpr Vector2 Position = Vector2(534, 279);

public:
	ModeMulti(SceneTitle* sceneTitleNode, SceneTitle::Mode mode) :
		ModeSelect(
			sceneTitleNode,
			mode,
			Position,
			"mode_multi.png",
			std::bind(&SceneTitle::MultiMode, sceneTitleNode)
		)
	{
	}
};