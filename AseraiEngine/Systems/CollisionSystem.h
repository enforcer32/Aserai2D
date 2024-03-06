#pragma once

#include "AseraiEngine/ECS/Registry.h"
#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Core/EventManager.h"
#include "AseraiEngine/Renderer/Renderer2D.h"
#include "AseraiEngine/Core/InputManager.h"

namespace Aserai
{
	class CollisionSystem : public System
	{
	public:
		CollisionSystem();

		void OnUpdate(DeltaTime dt, const std::shared_ptr<EventManager>& eventManager);
		void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer, const std::shared_ptr<InputManager>& inputManager);

	private:
		bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH);
	};
}
