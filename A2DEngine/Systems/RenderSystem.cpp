#include "A2DEnginePCH.h"
#include "A2DEngine/Systems/RenderSystem.h"
#include "A2DEngine/Components/TransformComponent.h"
#include "A2DEngine/Components/SpriteComponent.h"
#include "A2DEngine/Asset/AssetManager.h"

#include <array>

namespace Aserai2D
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
			transform.Scale.x *= sprite.Width;
			transform.Scale.y *= sprite.Height;

			if (sprite.Texture && AssetManager::IsAssetLoaded(sprite.Texture))
				renderer->RenderQuad(transform.GetTransform(), AssetManager::GetAsset<TextureAsset>(sprite.Texture)->GetTexture(), sprite.TextureUV);
			else
				renderer->RenderQuad(transform.GetTransform(), sprite.Color);
		}
	}
}
