#pragma once

#include "AseraiEditor/Panels/Panel.h"

#include <AseraiEngine/Scene/Scene.h>
#include <AseraiEngine/Utils/AssetManager.h>

namespace Aserai
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
