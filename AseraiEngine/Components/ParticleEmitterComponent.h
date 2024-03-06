#pragma once

#include "AseraiEngine/Utils/DateTime.h"
#include "AseraiEngine/Input/InputCodes.h"

#include <glm/glm.hpp>

namespace Aserai
{
	struct ParticleEmitterComponent
	{
		std::string Name;
		glm::vec3 Velocity;
		uint32_t Duration;
		uint32_t Frequency;
		uint32_t Hit;
		bool Friendly;
		bool Automatic;
		KeyCode Key;
		uint32_t LastEmitTime;

		ParticleEmitterComponent(const std::string& name = "particles", const glm::vec3& velocity = glm::vec3(1), uint32_t duration = 1, uint32_t frequency = 0, uint32_t hit = 0, bool friendly = false, bool automatic = true, KeyCode key = KeyCode::Space)
			: Name(name), Velocity(velocity), Duration(duration), Frequency(frequency), Hit(hit), Friendly(friendly), Automatic(automatic), Key(key)
		{
			LastEmitTime = DateTime::GetTimeSeconds();
		}
	};
}
