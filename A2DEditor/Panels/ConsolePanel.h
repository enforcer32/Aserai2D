#pragma once

#include "A2DEditor/Panels/Panel.h"

namespace Aserai2D
{
	class ConsolePanel : public Panel
	{
	public:
		virtual void OnImGuiRender() override;
	};
}
