#pragma once

#include "AseraiEditor/Panels/Panel.h"

#include <AseraiEngine/Scene/Scene.h>
#include <AseraiEngine/Core/InputManager.h>

namespace Aserai
{
	class SceneGraphPanel : public Panel
	{
	public:
		SceneGraphPanel(const std::shared_ptr<Scene>& scene, const std::shared_ptr<InputManager>& inputManager);

		virtual void OnImGuiRender() override;
		
		void SetScene(const std::shared_ptr<Scene>& scene);
		static Entity GetSelectedEntity();

	private:
		void RenderEntity(Entity& entity);

	private:
		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<InputManager> m_InputManager;
		static Entity s_SelectedEntity;
	};
}
