#pragma once

#include "AseraiEditor/Panels/Panel.h"

namespace Aserai
{
	class SceneGraphPanel : public Panel
	{
	public:
		virtual void OnImGuiRender() override;
	};
}
