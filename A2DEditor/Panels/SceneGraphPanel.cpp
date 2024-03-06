#include "A2DEditorPCH.h"
#include "A2DEditor/Panels/SceneGraphPanel.h"

#include <A2DEngine/Input/InputManager.h>

#include <imgui.h>

namespace Aserai2D
{
	Entity SceneGraphPanel::s_SelectedEntity{};

	SceneGraphPanel::SceneGraphPanel(const std::shared_ptr<Scene>& scene)
		: m_Scene(scene)
	{
	}

	void SceneGraphPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Graph");
		
		for (auto entity : m_Scene->GetRegistry()->GetEntities())
			RenderEntity(entity);

		if(InputManager::IsMousePressed(MouseCode::Button1) && ImGui::IsWindowHovered())
			s_SelectedEntity = {};

		if (ImGui::BeginPopupContextWindow(0, 1))
		{
			if (ImGui::MenuItem("Create Entity"))
				m_Scene->CreateEntity("Entity");

			ImGui::EndPopup();
		}
		
		ImGui::End();
	}

	void SceneGraphPanel::SetScene(const std::shared_ptr<Scene>& scene)
	{
		m_Scene = scene;
	}

	Entity SceneGraphPanel::GetSelectedEntity()
	{
		return s_SelectedEntity;
	}

	void SceneGraphPanel::RenderEntity(Entity& entity)
	{
		bool remove = false;

		ImGuiTreeNodeFlags flags = ((entity == s_SelectedEntity && s_SelectedEntity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool open = ImGui::TreeNodeEx((void*)entity.GetID(), flags, entity.GetTag().c_str());

		if (ImGui::IsItemClicked())
			s_SelectedEntity = entity;

		if (ImGui::BeginPopupContextItem(0, 1))
		{
			if (ImGui::MenuItem("Delete Entity"))
				remove = true;

			ImGui::EndPopup();
		}

		if (open)
			ImGui::TreePop();

		if (remove)
		{
			m_Scene->DestroyEntity(entity);
			if (s_SelectedEntity == entity)
				s_SelectedEntity = {};
		}
	}
}
