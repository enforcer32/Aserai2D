#include "A2DEnginePCH.h"
#include "A2DEngine/Systems/KeyboardMovementSystem.h"
#include "A2DEngine/Input/InputManager.h"
#include "A2DEngine/Components/TransformComponent.h"
#include "A2DEngine/Components/KeyboardMovementComponent.h"

namespace Aserai2D
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
