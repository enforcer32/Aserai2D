#pragma once

#include "A2DEngine/Events/Event.h"
#include "A2DEngine/ECS/Registry.h"

namespace Aserai2D
{
	class CollisionEvent : public Event
	{
	public:
		Entity entityA;
		Entity entityB;

		CollisionEvent(Entity a, Entity b)
			: entityA(a), entityB(b) {}
	};
}
