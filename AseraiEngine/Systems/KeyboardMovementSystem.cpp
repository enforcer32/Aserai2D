#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/KeyboardMovementSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/KeyboardMovementComponent.h"
#include "AseraiEngine/Components/SpriteComponent.h"

namespace Aserai
{
	KeyboardMovementSystem::KeyboardMovementSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<KeyboardMovementComponent>();
	}

	void KeyboardMovementSystem::OnUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager)
	{
		for (auto& entity : GetEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& keyboard = entity.GetComponent<KeyboardMovementComponent>();
			bool hasSprit = entity.HasComponent<SpriteComponent>();

			if (inputManager->IsKeyPressed(keyboard.LeftKey))
			{
				transform.Translation.x -= keyboard.Speed * dt;

				if (hasSprit)
					transform.Rotation2D = 90.0f;
			}
			else if (inputManager->IsKeyPressed(keyboard.RightKey))
			{
				transform.Translation.x += keyboard.Speed * dt;
				if (hasSprit)
					transform.Rotation2D = -90.0f;
			}
			else if (inputManager->IsKeyPressed(keyboard.UpKey))
			{
				transform.Translation.y += keyboard.Speed * dt;
				if (hasSprit)
					transform.Rotation2D = 0.0;

			}
			else if (inputManager->IsKeyPressed(keyboard.DownKey))
			{
				transform.Translation.y -= keyboard.Speed * dt;
				if (hasSprit)
					transform.Rotation2D = 180.0f;
			}
		}
	}
}
