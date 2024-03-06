#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/MovementSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/RigidBodyComponent.h"

namespace Aserai
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
			float dtf = dt;
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
			transform.Translation += rigidbody.Velocity * dtf;
		}
	}
}
