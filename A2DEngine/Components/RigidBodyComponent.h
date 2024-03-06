#pragma once

#include <glm/glm.hpp>

namespace Aserai2D
{
	struct RigidBodyComponent
	{
		glm::vec3 Velocity;

		RigidBodyComponent(const glm::vec3& velocity = glm::vec3(0.0f, 0.0f, 0.0f))
			: Velocity(velocity)
		{
		}
	};
}
