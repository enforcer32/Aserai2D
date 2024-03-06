#include "A2DEnginePCH.h"
#include "A2DEngine/Core/EventManager.h"

namespace Aserai2D
{
	bool EventManager::Init()
	{
		return m_Initialized = true;
	}

	void EventManager::Destroy()
	{
		m_Initialized = false;
	}
}
