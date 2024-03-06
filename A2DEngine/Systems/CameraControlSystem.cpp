#include "A2DEnginePCH.h"
#include "A2DEngine/Systems/CameraControlSystem.h"
#include "A2DEngine/Input/InputManager.h"
#include "A2DEngine/Components/TransformComponent.h"
#include "A2DEngine/Components/CameraComponent.h"

namespace Aserai2D
{
	CameraControlSystem::CameraControlSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<CameraComponent>();
	}

	void CameraControlSystem::OnUpdate(DeltaTime dt)
	{
		for (auto& entity : GetEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& camera = entity.GetComponent<CameraComponent>();

			if (camera.Primary)
			{
				if (InputManager::IsKeyPressed(KeyCode::A))
					transform.Translation.x -= camera.Speed * dt;
				if (InputManager::IsKeyPressed(KeyCode::D))
					transform.Translation.x += camera.Speed * dt;
				if (InputManager::IsKeyPressed(KeyCode::W))
					transform.Translation.y += camera.Speed * dt;
				if (InputManager::IsKeyPressed(KeyCode::S))
					transform.Translation.y -= camera.Speed * dt;
			}
		}
	}
}
