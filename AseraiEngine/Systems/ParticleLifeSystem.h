#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"

namespace Aserai
{
	class ParticleLifeSystem : public System
	{
	public:
		ParticleLifeSystem();

		void OnUpdate(DeltaTime dt);
	};
}
