#pragma once

#include "A2DEngine/ECS/Registry.h"
#include "A2DEngine/Core/DeltaTime.h"

namespace Aserai2D
{
	class KeyboardMovementSystem : public System
	{
	public:
		KeyboardMovementSystem();

		void OnUpdate(DeltaTime dt);
	};
}
