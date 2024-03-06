#pragma once

#include "A2DEditor/Panels/Panel.h"

#include <A2DEngine/Scene/Scene.h>

namespace Aserai2D
{
	class SceneGraphPanel : public Panel
	{
	public:
		SceneGraphPanel(const std::shared_ptr<Scene>& scene);

		virtual void OnImGuiRender() override;
		
		void SetScene(const std::shared_ptr<Scene>& scene);
		static Entity GetSelectedEntity();

	private:
		void RenderEntity(Entity& entity);

	private:
		std::shared_ptr<Scene> m_Scene;
		static Entity s_SelectedEntity;
	};
}
