#pragma once

#include "AseraiEngine/Utils/DateTime.h"

#include <glm/glm.hpp>

namespace Aserai
{
	struct ParticleEmitterComponent
	{
		glm::vec3 Velocity;
		uint32_t Duration;
		uint32_t Frequency;
		uint32_t Hit;
		bool Friendly;
		uint32_t LastEmitTime;

		ParticleEmitterComponent(const glm::vec3& velocity = glm::vec3(0), uint32_t duration = 1, uint32_t frequency = 0, uint32_t hit = 0, bool friendly = false)
			: Velocity(velocity), Duration(duration), Frequency(frequency), Hit(hit), Friendly(friendly)
		{
			LastEmitTime = DateTime::GetTimeSeconds();
		}
	};
}
