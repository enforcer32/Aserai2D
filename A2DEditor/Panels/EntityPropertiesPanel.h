#pragma once

#include "A2DEditor/Panels/Panel.h"

#include <A2DEngine/Scene/Scene.h>
#include <A2DEngine/Utils/AssetManager.h>

namespace Aserai2D
{
	class EntityPropertiesPanel : public Panel
	{
	public:
		EntityPropertiesPanel(const std::shared_ptr<AssetManager>& assetManager);

		virtual void OnImGuiRender() override;

	private:
		void RenderEntityProperties(Entity& entity);

	private:
		std::shared_ptr<AssetManager> m_AssetManager;
	};
}
