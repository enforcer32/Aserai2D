#include "A2DEnginePCH.h"
#include "A2DEngine/Systems/MovementSystem.h"
#include "A2DEngine/Components/TransformComponent.h"
#include "A2DEngine/Components/RigidBodyComponent.h"

namespace Aserai2D
{
	MovementSystem::MovementSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<RigidBodyComponent>();
	}

	void MovementSystem::OnUpdate(DeltaTime dt)
	{
		for (auto& entity : GetEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
			transform.Translation += rigidbody.Velocity * (float)dt;
		}
	}
}
