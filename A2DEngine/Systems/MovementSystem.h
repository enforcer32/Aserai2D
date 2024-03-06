#pragma once

#include "A2DEngine/ECS/Registry.h"
#include "A2DEngine/Core/DeltaTime.h"

namespace Aserai2D
{
	class MovementSystem : public System
	{
	public:
		MovementSystem();

		void OnUpdate(DeltaTime dt);
	};
}
