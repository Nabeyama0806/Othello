#pragma once
#include "ModeSelect.h"
#include "SceneTitle.h"

class ModeWatch : public ModeSelect
{
private:
	static constexpr Vector2 Position = Vector2(534, 419);

public:
	ModeWatch(SceneTitle* sceneTitleNode, SceneTitle::Mode mode) :
		ModeSelect(
			sceneTitleNode,
			mode,
			Position,
			"mode_watch.png",
			std::bind(&SceneTitle::WatchMode, sceneTitleNode)
		)
	{
	}
};