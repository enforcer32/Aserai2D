#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/CameraControlSystem.h"
#include "AseraiEngine/Input/InputManager.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/CameraComponent.h"

namespace Aserai
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
