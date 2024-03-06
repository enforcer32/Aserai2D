#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/CameraControlSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/CameraComponent.h"

namespace Aserai
{
	CameraControlSystem::CameraControlSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<CameraComponent>();
	}

	void CameraControlSystem::OnUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager)
	{
		for (auto& entity : GetEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& camera = entity.GetComponent<CameraComponent>();

			if (camera.Primary)
			{
				if (inputManager->IsKeyPressed(KeyCode::A))
					transform.Translation.x -= camera.Speed * dt;
				if (inputManager->IsKeyPressed(KeyCode::D))
					transform.Translation.x += camera.Speed * dt;
				if (inputManager->IsKeyPressed(KeyCode::W))
					transform.Translation.y += camera.Speed * dt;
				if (inputManager->IsKeyPressed(KeyCode::S))
					transform.Translation.y -= camera.Speed * dt;
			}
		}
	}
}
