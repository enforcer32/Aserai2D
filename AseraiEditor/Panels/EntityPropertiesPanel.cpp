#include "AseraiEditorPCH.h"
#include "AseraiEditor/Panels/EntityPropertiesPanel.h"
#include "AseraiEditor/Panels/SceneGraphPanel.h"

#include <AseraiEngine/Components/TransformComponent.h>
#include <AseraiEngine/Components/SpriteComponent.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Aserai
{
	template<typename T, typename UIFunction>
	static void RenderComponent(const std::string& name, Entity& entity, UIFunction func)
	{
		const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<T>())
		{
			bool remove = false;
			auto& component = entity.GetComponent<T>();

			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeFlags, name.c_str());

			ImGui::SameLine();
			if (ImGui::Button("-"))
				remove = true;

			if (open)
			{
				func(component);
				ImGui::TreePop();
			}

			if (remove)
				entity.RemoveComponent<T>();
		}
	}

	template<typename T>
	static void RenderAddComponent(const std::string& name, Entity& entity)
	{
		if (!entity.HasComponent<T>())
		{
			if (ImGui::MenuItem(name.c_str()))
			{
				entity.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}

	void EntityPropertiesPanel::OnImGuiRender()
	{
		ImGui::Begin("Properties");
		Entity selectedEntity = SceneGraphPanel::GetSelectedEntity();
		if (selectedEntity)
		{
			if (ImGui::Button("Add Component", { 250.0, 20.0 }))
				ImGui::OpenPopup("AddComponent");
			ImGui::InvisibleButton("###addComponentPadding", { 250.0, 20.0 });

			RenderEntityProperties(selectedEntity);

			if (ImGui::BeginPopup("AddComponent"))
			{
				RenderAddComponent<TransformComponent>("Transform", selectedEntity);
				RenderAddComponent<SpriteComponent>("Sprite", selectedEntity);
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}

	void EntityPropertiesPanel::RenderEntityProperties(Entity& entity)
	{
		// ID
		ImGui::Text("ID: %d\n", entity.GetID());

		// Tag
		char bufftag[1024] = {};
		strcpy_s(bufftag, sizeof(bufftag), entity.GetTag().c_str());
		ImGui::Text("Tag");
		ImGui::SameLine();
		if (ImGui::InputText("##Tag", bufftag, sizeof(bufftag)))
			entity.SetTag(bufftag);

		// Group
		char buffgroup[1024] = {};
		strcpy_s(buffgroup, sizeof(buffgroup), entity.GetGroup().c_str());
		ImGui::Text("Group");
		ImGui::SameLine();
		if (ImGui::InputText("##Group", buffgroup, sizeof(buffgroup)))
			entity.SetGroup(buffgroup);

		// Components
		RenderComponent<TransformComponent>("Transform", entity, [](TransformComponent& component)
			{
				ImGui::Text("Translation");
				ImGui::SameLine();
				ImGui::DragFloat3("##Translation", glm::value_ptr(component.Translation), 0.1f, 0.0f, 0.0f, "%.2f");
				
				ImGui::Text("Rotation");
				ImGui::SameLine();
				glm::vec3 rotation = glm::degrees(component.Rotation);
				if (ImGui::DragFloat3("##Rotation", glm::value_ptr(rotation), 0.1f, 0.0f, 0.0f, "%.2f"))
					component.Rotation = glm::radians(rotation);

				ImGui::Text("Scale");
				ImGui::SameLine();
				ImGui::DragFloat3("##Scale", glm::value_ptr(component.Scale), 0.1f, 0.0f, 0.0f, "%.2f");

				ImGui::Text("Rotation 2D");
				ImGui::SameLine();
				ImGui::DragFloat("##Rotation 2D", &component.Rotation2D, 1.0f, 0.0f, 360.0f, "%.2f");
			});

		RenderComponent<SpriteComponent>("Sprite", entity, [](SpriteComponent& component)
			{
				if (!component.Texture)
				{
					ImGui::Text("Color");
					ImGui::SameLine();
					ImGui::ColorEdit4("##Color", glm::value_ptr(component.Color));
				}

				ImGui::Text("Width");
				ImGui::SameLine();
				ImGui::DragInt("##Width", (int32_t*)&component.Width, 1.0f);


				ImGui::Text("Height");
				ImGui::SameLine();
				ImGui::DragInt("##Height", (int32_t*)&component.Height, 1.0f);


				ImGui::Text("Z-Index");
				ImGui::SameLine();
				ImGui::DragInt("##Z-Index", (int32_t*)&component.ZIndex, 1.0f);
			});
	}
}