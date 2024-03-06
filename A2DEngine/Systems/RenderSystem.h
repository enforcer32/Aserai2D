#pragma once

#include "A2DEngine/ECS/Registry.h"
#include "A2DEngine/Core/DeltaTime.h"
#include "A2DEngine/Renderer/Renderer2D.h"

#include <memory>

namespace Aserai2D
{
	class RenderSystem : public System
	{
	public:
		RenderSystem();

		void OnUpdate(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer);
	};
}
