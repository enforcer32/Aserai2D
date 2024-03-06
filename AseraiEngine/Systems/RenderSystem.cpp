#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/RenderSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/SpriteComponent.h"

#include <array>

namespace Aserai
{
	RenderSystem::RenderSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<SpriteComponent>();
	}

	void RenderSystem::OnUpdate(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer)
	{
		struct EntityComponents
		{
			TransformComponent TransformComponent;
			SpriteComponent SpriteComponent;
		};

		std::vector<EntityComponents> entities;
		for (auto entity : GetEntities())
		{
			EntityComponents entityComponents;
			entityComponents.TransformComponent = entity.GetComponent<TransformComponent>();
			entityComponents.SpriteComponent = entity.GetComponent<SpriteComponent>();
			entities.emplace_back(entityComponents);
		}

		std::sort(entities.begin(), entities.end(), [](const EntityComponents& e1, const EntityComponents& e2) {
			return e1.SpriteComponent.ZIndex < e2.SpriteComponent.ZIndex;
			});

		for (auto& entity : entities)
		{
			auto transform = entity.TransformComponent;
			const auto& sprite = entity.SpriteComponent;
		
			if (sprite.Texture)
			{
				if (sprite.TextureX || sprite.TextureY || sprite.TextureH || sprite.TextureW)
				{
					std::array<glm::vec2, 4> textureUV;
					textureUV[0] = { ((float)(sprite.TextureX * sprite.TextureW) / sprite.Texture->GetWidth()), ((float)(sprite.TextureY * sprite.TextureH) / sprite.Texture->GetHeight()) }; // BOTTOM LEFT
					textureUV[1] = { ((float)((sprite.TextureX + 1) * sprite.TextureW) / sprite.Texture->GetWidth()), ((float)(sprite.TextureY * sprite.TextureH) / sprite.Texture->GetHeight()) }; // BOTTOM RIGHT
					textureUV[2] = { ((float)((sprite.TextureX + 1) * sprite.TextureW) / sprite.Texture->GetWidth()), ((float)((sprite.TextureY + 1) * sprite.TextureH) / sprite.Texture->GetHeight()) }; // TOP RIGHT
					textureUV[3] = { ((float)(sprite.TextureX * sprite.TextureW) / sprite.Texture->GetWidth()), ((float)((sprite.TextureY + 1) * sprite.TextureH) / sprite.Texture->GetHeight()) }; // TOP LEFT
					transform.Scale.x *= sprite.Width;
					transform.Scale.y *= sprite.Height;
					renderer->RenderQuad(transform.GetTransform(), sprite.Texture, textureUV);
				}
				else
				{
					renderer->RenderQuad(transform.GetTransform(), sprite.Texture);
				}
			}
			else
			{
				renderer->RenderQuad(transform.GetTransform(), sprite.Color);
			}
		}
	}
}
