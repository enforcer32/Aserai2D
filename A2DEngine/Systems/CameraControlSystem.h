#pragma once

#include "A2DEngine/ECS/Registry.h"
#include "A2DEngine/Core/DeltaTime.h"

namespace Aserai2D
{
	class CameraControlSystem : public System
	{
	public:
		CameraControlSystem();

		void OnUpdate(DeltaTime dt);
	};
}
