#include "A2DEditorPCH.h"
#include "A2DEditor/Panels/AssetManagerPanel.h"

#include <A2DEngine/Core/Logger.h>
#include <A2DEngine/Asset/AssetManager.h>
#include <A2DEngine/Asset/TextureAsset.h>
#include <A2DEngine/Platform/FileDialog.h>
#include <A2DEngine/Components/TransformComponent.h>
#include <A2DEngine/Components/SpriteComponent.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Aserai2D
{
	AssetManagerPanel::AssetManagerPanel(const std::shared_ptr<Scene>& scene)
		: m_Scene(scene), m_HoldingEntity{}
	{
	}

	void AssetManagerPanel::OnImGuiRender()
	{
		ImGui::Begin("AssetManager");

		if (ImGui::BeginTabBar("AssetManager Tabs"))
		{
			RenderTextureTab();
			RenderSpritesheetTab();

			ImGui::EndTabBar();
		}

		ImGui::End();
	}

	void AssetManagerPanel::RenderTextureTab()
	{
		if (ImGui::BeginTabItem("Textures"))
		{
			if (ImGui::Button("Add Texture"))
				ImGui::OpenPopup("AddTexturePopup");

			if (ImGui::BeginPopupModal("AddTexturePopup"))
			{
				if (ImGui::Button("Close"))
					ImGui::CloseCurrentPopup();

				if (ImGui::ImageButton("##TextureAdd", (void*)0, ImVec2(100.f, 100.f), ImVec2(0, 1), ImVec2(1, 0)))
				{
					std::string texturePath = FileDialog::OpenFile("Image Files (*.png, *.jpg, *.jpeg)\0*.png;*.jpg;*.jpeg\0");
					if (!texturePath.empty())
						AssetManager::CreateAsset<TextureAsset>(texturePath);
				}

				ImGui::EndPopup();
			}

			for (auto& asset : AssetManager::GetAssets<TextureAsset>())
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth;
				bool open = ImGui::TreeNodeEx((void*)(uint64_t)asset->GetAssetID(), flags, (asset->GetTexturePath() + ":" + std::to_string((uint64_t)asset->GetAssetID())).c_str());
				if (open)
				{
					ImGui::ImageButton(("##TextureList" + std::to_string(asset->GetAssetID())).c_str(), (void*)(asset->IsLoaded() ? asset->GetTexture()->GetID() : 0), ImVec2(100.f, 100.f), ImVec2(0, 1), ImVec2(1, 0));
					ImGui::TreePop();
				}
			}

			ImGui::EndTabItem();
		}
	}

	void AssetManagerPanel::RenderSpritesheetTab()
	{
		if (ImGui::BeginTabItem("Spritesheet"))
		{
			auto& itemSpacing = ImGui::GetStyle().ItemSpacing;
			float windowX2 = ImGui::GetWindowPos().x + ImGui::GetWindowSize().x;

			for (auto& spritesheetAsset : AssetManager::GetAssets<SpritesheetAsset>())
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth;
				bool open = ImGui::TreeNodeEx((void*)(uint64_t)spritesheetAsset->GetAssetID(), flags, (spritesheetAsset->GetName() + ":" + std::to_string((uint64_t)spritesheetAsset->GetAssetID())).c_str());
				if (open)
				{
					auto texture = AssetManager::GetAsset<TextureAsset>(spritesheetAsset->GetTexture())->GetTexture();
					for (uint32_t i = 0; i < spritesheetAsset->GetSpriteCount(); i++)
					{
						auto& textureUV = spritesheetAsset->GetSprite(i).TextureUV;
						if (ImGui::ImageButton((std::string("##Texture" + std::to_string(i))).c_str(), (void*)texture->GetID(), ImVec2(50.0f, 50.0f), ImVec2(textureUV[0].x, textureUV[0].y), ImVec2(textureUV[2].x, textureUV[2].y)))
						{
							ASERAI_LOG_INFO("Generating Sprite({})", i);
							Entity entity = GenerateSpriteEntity(spritesheetAsset->GetSprite(i), glm::vec3(1.0f, 1.0f, 1.0f));
							m_HoldingEntity = entity;
						}

						float lastX2 = ImGui::GetItemRectMax().x;
						float nextX2 = lastX2 + itemSpacing.x + spritesheetAsset->GetSpriteWidth();

						if ((i + 1) < spritesheetAsset->GetSpriteCount() && nextX2 < windowX2)
							ImGui::SameLine();
					}

					ImGui::TreePop();
				}
			}

			ImGui::EndTabItem();
		}
	}

	Entity AssetManagerPanel::GenerateSpriteEntity(const Sprite& sprite, const glm::vec3& scale)
	{
		Entity entity = m_Scene->CreateEntity("Entity");
		entity.GetComponent<TransformComponent>().Scale = scale;
		entity.AddComponent<SpriteComponent>(sprite.Texture, 1, 1, 0, sprite.TextureUV);
		return entity;
	}
}
