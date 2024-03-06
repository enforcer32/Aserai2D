#include "A2DEditorPCH.h"
#include "A2DEditor/Panels/SpritesheetPanel.h"

#include <A2DEngine/Core/Logger.h>
#include <A2DEngine/Components/TransformComponent.h>
#include <A2DEngine/Components/SpriteComponent.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Aserai2D
{
	SpritesheetPanel::SpritesheetPanel(const std::shared_ptr<Scene>& scene)
		: m_Scene(scene), m_HoldingEntity{}
	{
	}

	void SpritesheetPanel::OnImGuiRender()
	{
		ImGui::Begin("Spritesheet Panel");

		auto& itemSpacing = ImGui::GetStyle().ItemSpacing;
		float windowX2 = ImGui::GetWindowPos().x + ImGui::GetWindowSize().x;

		auto textureID = AssetManager::CreateAsset<TextureAsset>("../Assets/Spritesheets/top_down_tanks.png");
		auto spritesheetID = AssetManager::CreateAsset<SpritesheetAsset>(textureID, 128, 128, 32, 0);
		auto spritesheetAsset = AssetManager::GetAsset<SpritesheetAsset>(spritesheetID);
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

		ImGui::End();
	}

	Entity SpritesheetPanel::GenerateSpriteEntity(const Sprite& sprite, const glm::vec3& scale)
	{
		Entity entity = m_Scene->CreateEntity("Entity");
		entity.GetComponent<TransformComponent>().Scale = scale;
		entity.AddComponent<SpriteComponent>(sprite.Texture, 1, 1, 0, sprite.TextureUV);
		return entity;
	}
}
