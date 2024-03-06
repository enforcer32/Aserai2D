#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"

namespace Aserai
{
	class KeyboardMovementSystem : public System
	{
	public:
		KeyboardMovementSystem();

		void OnUpdate(DeltaTime dt);
	};
}
