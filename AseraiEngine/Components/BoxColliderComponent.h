#pragma once

#include <glm/glm.hpp>

namespace Aserai
{
	struct BoxColliderComponent
	{
		uint32_t Width;
		uint32_t Height;
		glm::vec2 Offset;

		BoxColliderComponent(uint32_t width = 0, uint32_t height = 0, glm::vec2 offset = glm::vec2(0))
			: Width(width), Height(height), Offset(offset)
		{
		}
	};
}
