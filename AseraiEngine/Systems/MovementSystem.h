#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"

namespace Aserai
{
	class MovementSystem : public System
	{
	public:
		MovementSystem();

		void Update(DeltaTime dt);
	};
}
