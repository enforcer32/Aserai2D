#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Renderer/Renderer2D.h"

#include <memory>

namespace Aserai
{
	class RenderSystem : public System
	{
	public:
		RenderSystem();

		void OnUpdate(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer);
	};
}
