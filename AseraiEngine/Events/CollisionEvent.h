#pragma once

#include "AseraiEngine/Events/Event.h"
#include "AseraiEngine/ECS/Registry.h"

namespace Aserai
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
