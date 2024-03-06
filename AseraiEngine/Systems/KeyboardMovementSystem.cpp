#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/KeyboardMovementSystem.h"
#include "AseraiEngine/Input/InputManager.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/KeyboardMovementComponent.h"

namespace Aserai
{
	KeyboardMovementSystem::KeyboardMovementSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<KeyboardMovementComponent>();
	}

	void KeyboardMovementSystem::OnUpdate(DeltaTime dt)
	{
		for (auto& entity : GetEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& keyboard = entity.GetComponent<KeyboardMovementComponent>();

			if (InputManager::IsKeyPressed(keyboard.LeftKey))
			{
				transform.Translation.x -= keyboard.Speed * dt;
				if(keyboard.UpdateRotation2D)
					transform.Rotation2D = 90.0f;
			}
			else if (InputManager::IsKeyPressed(keyboard.RightKey))
			{
				transform.Translation.x += keyboard.Speed * dt;
				if (keyboard.UpdateRotation2D)
					transform.Rotation2D = -90.0f;
			}
			else if (InputManager::IsKeyPressed(keyboard.UpKey))
			{
				transform.Translation.y += keyboard.Speed * dt;
				if (keyboard.UpdateRotation2D)
					transform.Rotation2D = 0.0;

			}
			else if (InputManager::IsKeyPressed(keyboard.DownKey))
			{
				transform.Translation.y -= keyboard.Speed * dt;
				if (keyboard.UpdateRotation2D)
					transform.Rotation2D = 180.0f;
			}
		}
	}
}
