#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/RenderSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/SpriteComponent.h"

namespace Aserai
{
	RenderSystem::RenderSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<SpriteComponent>();
	}

	void RenderSystem::Update(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer)
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
			const auto& transform = entity.TransformComponent;
			const auto& sprite = entity.SpriteComponent;

			if (sprite.Texture)
				renderer->RenderQuad(transform.GetTransform(), sprite.Texture);
			else
				renderer->RenderQuad(transform.GetTransform(), sprite.Color);
		}
	}
}
