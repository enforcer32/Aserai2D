#pragma once

#include "A2DEditor/Panels/Panel.h"

#include <A2DEngine/Scene/Scene.h>
#include <A2DEngine/Asset/SpritesheetAsset.h>

#include <glm/glm.hpp>

namespace Aserai2D
{
	class SpritesheetPanel : public Panel
	{
	public:
		SpritesheetPanel(const std::shared_ptr<Scene>& scene);

		virtual void OnImGuiRender() override;

	private:
		Entity GenerateSpriteEntity(const Sprite& sprite, const glm::vec3& scale);

	private:
		std::shared_ptr<Scene> m_Scene;
		Entity m_HoldingEntity;
	};
}
