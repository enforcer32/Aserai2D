#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Core/InputManager.h"

namespace Aserai
{
	class ParticleEmitSystem : public System
	{
	public:
		ParticleEmitSystem();

		void OnUpdate(DeltaTime dt, const std::shared_ptr<Registry>& registry, const std::shared_ptr<InputManager>& inputManager);
	};
}
