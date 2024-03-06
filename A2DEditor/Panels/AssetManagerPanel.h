#pragma once

#include "A2DEditor/Panels/Panel.h"

#include <A2DEngine/Scene/Scene.h>

#include <A2DEngine/Asset/SpritesheetAsset.h>
#include <glm/glm.hpp>

namespace Aserai2D
{
	class AssetManagerPanel : public Panel
	{
	public:
		AssetManagerPanel(const std::shared_ptr<Scene>& scene, const std::shared_ptr<EditorCamera>& editorCamera);

		virtual void OnImGuiRender() override;

	private:
		void RenderTextureTab();
		void RenderSpritesheetTab();

	private:
		Entity GenerateSpriteEntity(const Sprite& sprite, const glm::vec3& scale);
		void OnPickupSpriteEntity();

	private:
		glm::vec2 ConvertScreenToWorldCoordinates(const glm::vec2& screen);

	private:
		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<EditorCamera> m_EditorCamera;
		Entity m_HoldingSpriteEntity;
	};
}
