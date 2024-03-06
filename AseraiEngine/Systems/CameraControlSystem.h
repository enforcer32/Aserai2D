#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"

namespace Aserai
{
	class CameraControlSystem : public System
	{
	public:
		CameraControlSystem();

		void OnUpdate(DeltaTime dt);
	};
}
