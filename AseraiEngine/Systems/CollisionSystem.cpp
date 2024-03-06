#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/CollisionSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/BoxColliderComponent.h"
#include "AseraiEngine/Events/CollisionEvent.h"

namespace Aserai
{
	CollisionSystem::CollisionSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<BoxColliderComponent>();
	}

	void CollisionSystem::OnUpdate(DeltaTime dt, const std::shared_ptr<EventManager>& eventManager)
	{
		auto& entities = GetEntities();
		for (auto itA = entities.begin(); itA != entities.end(); itA++)
		{
			Entity entityA = *itA;
			auto& transformA = entityA.GetComponent<TransformComponent>();
			const auto& boxColliderA = entityA.GetComponent<BoxColliderComponent>();

			for (auto itB = itA; itB != entities.end(); itB++)
			{
				Entity entityB = *itB;
				if (entityA == entityB) continue;

				auto& transformB = entityB.GetComponent<TransformComponent>();
				const auto& boxColliderB = entityB.GetComponent<BoxColliderComponent>();

				bool collision = CheckAABBCollision(transformA.Translation.x + boxColliderA.Offset.x, transformA.Translation.y + boxColliderA.Offset.y, boxColliderA.Width, boxColliderA.Height, transformB.Translation.x + boxColliderB.Offset.x, transformB.Translation.y + boxColliderB.Offset.y, boxColliderB.Width, boxColliderB.Height);
				if (collision)
					eventManager->Emit<CollisionEvent>(entityA, entityB);
			}
		}
	}

	void CollisionSystem::OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer, const std::shared_ptr<InputManager>& inputManager)
	{
		for (auto& entity : GetEntities())
		{
			if (inputManager->IsKeyHeldDown(KeyCode::B))
			{
				auto transform = entity.GetComponent<TransformComponent>();
				const auto& boxCollider = entity.GetComponent<BoxColliderComponent>();
				transform.Translation.x += boxCollider.Offset.x;
				transform.Translation.y += boxCollider.Offset.y;
				transform.Scale.x *= boxCollider.Width;
				transform.Scale.y *= boxCollider.Height;

				renderer->RenderQuad(transform.GetTransform(), { 255.0, 255.0, 0.0, 255.0 });
			}
		}
	}

	bool CollisionSystem::CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH)
	{
		return (aX < bX + bW &&	aX + aW > bX &&	aY < bY + bH &&	aY + aH > bY);
	}
}
