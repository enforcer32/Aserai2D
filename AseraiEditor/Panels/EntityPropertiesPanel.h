#pragma once

#include "AseraiEditor/Panels/Panel.h"

#include <AseraiEngine/Scene/Scene.h>

namespace Aserai
{
	class EntityPropertiesPanel : public Panel
	{
	public:
		virtual void OnImGuiRender() override;

	private:
		void RenderEntityProperties(Entity& entity);
	};
}
