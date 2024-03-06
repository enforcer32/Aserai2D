#pragma once

#include "AseraiEditor/Panels/Panel.h"

#include <AseraiEngine/Scene/Scene.h>

namespace Aserai
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
