#include "A2DEditorPCH.h"
#include "A2DEditor/Panels/EntityPropertiesPanel.h"
#include "A2DEditor/Panels/SceneGraphPanel.h"

#include <A2DEngine/Components/TransformComponent.h>
#include <A2DEngine/Components/SpriteComponent.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Aserai2D
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
		ImGui::Text("UUID: %s\n", std::to_string(entity.GetUUID()).c_str());

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
				ImGui::Text("Color");
				ImGui::SameLine();
				ImGui::ColorEdit4("##Color", glm::value_ptr(component.Color));

				ImGui::Text("Width");
				ImGui::SameLine();
				ImGui::DragInt("##Width", (int32_t*)&component.Width, 1.0f);

				ImGui::Text("Height");
				ImGui::SameLine();
				ImGui::DragInt("##Height", (int32_t*)&component.Height, 1.0f);

				ImGui::Text("Z-Index");
				ImGui::SameLine();
				ImGui::DragInt("##Z-Index", (int32_t*)&component.ZIndex, 1.0f);

				ImGui::Text("Fixed");
				ImGui::SameLine();
				ImGui::Checkbox("##Fixed", &component.Fixed);

				ImGui::InvisibleButton("##texturePadding", { 10.0, 20.0 });

				ImGui::Text("Texture");
				ImGui::SameLine();
				if (ImGui::ImageButton("##Texture", (void*)((component.Texture && AssetManager::IsAssetLoaded(component.Texture)) ? AssetManager::GetAsset<TextureAsset>(component.Texture)->GetTexture()->GetID() : 0), ImVec2(100.f, 100.f), ImVec2(0, 1), ImVec2(1, 0)))
					ImGui::OpenPopup("AddSpriteTexturePopup");

				if (ImGui::BeginPopupModal("AddSpriteTexturePopup"))
				{
					if (ImGui::Button("Close"))
						ImGui::CloseCurrentPopup();

					for (auto& asset : AssetManager::GetAssets<TextureAsset>())
						if (ImGui::ImageButton(("##TextureAddSprite" + std::to_string((uint64_t)asset->GetAssetID())).c_str(), (void*)(asset->IsLoaded() ? asset->GetTexture()->GetID() : 0), ImVec2(100.f, 100.f), ImVec2(0, 1), ImVec2(1, 0)))
							component.Texture = asset->GetAssetID();

					ImGui::EndPopup();
				}

				ImGui::Text("TextureUV(0)");
				ImGui::SameLine();
				ImGui::DragFloat2("##TextureUV(0)", glm::value_ptr(component.TextureUV[0]), 0.1, 0, 1);

				ImGui::Text("TextureUV(1)");
				ImGui::SameLine();
				ImGui::DragFloat2("##TextureUV(1)", glm::value_ptr(component.TextureUV[1]), 0.1, 0, 1);

				ImGui::Text("TextureUV(2)");
				ImGui::SameLine();
				ImGui::DragFloat2("##TextureUV(2)", glm::value_ptr(component.TextureUV[2]), 0.1, 0, 1);

				ImGui::Text("TextureUV(3)");
				ImGui::SameLine();
				ImGui::DragFloat2("##TextureUV(3)", glm::value_ptr(component.TextureUV[3]), 0.1, 0, 1);

				if (ImGui::Button("Reset"))
					component.TextureUV = { glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 1.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } };
			});
	}
}
