#include "A2DEditorPCH.h"
#include "A2DEditor/Panels/AssetManagerPanel.h"

#include <A2DEngine/Core/Logger.h>
#include <A2DEngine/Asset/AssetManager.h>
#include <A2DEngine/Asset/TextureAsset.h>
#include <A2DEngine/Platform/FileDialog.h>

#include <imgui.h>

namespace Aserai2D
{
	void AssetManagerPanel::OnImGuiRender()
	{
		ImGui::Begin("AssetManager");

		if (ImGui::BeginTabBar("AssetManager Tabs"))
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

			ImGui::EndTabBar();
		}

		ImGui::End();
	}
}
