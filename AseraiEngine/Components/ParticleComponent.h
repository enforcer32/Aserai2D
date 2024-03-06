#pragma once

#include "AseraiEngine/Utils/DateTime.h"

#include <glm/glm.hpp>

namespace Aserai
{
	struct ParticleComponent
	{
		uint32_t Duration;
		uint32_t Hit;
		bool Friendly;
		uint32_t StartTime;

		ParticleComponent(uint32_t duration = 0, uint32_t hit = 0, bool friendly = false)
			: Duration(duration), Hit(hit), Friendly(friendly)
		{
			StartTime = DateTime::GetTimeSeconds();
		}
	};
}
