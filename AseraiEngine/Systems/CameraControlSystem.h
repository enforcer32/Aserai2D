#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Core/InputManager.h"

namespace Aserai
{
	class CameraControlSystem : public System
	{
	public:
		CameraControlSystem();

		void OnUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager);
	};
}
