#pragma once

#include "A2DEditor/Panels/Panel.h"

#include <A2DEngine/Scene/Scene.h>

namespace Aserai2D
{
	class EntityPropertiesPanel : public Panel
	{
	public:
		virtual void OnImGuiRender() override;

	private:
		void RenderEntityProperties(Entity& entity);
	};
}
