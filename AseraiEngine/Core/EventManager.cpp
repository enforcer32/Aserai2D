#include "AseraiEnginePCH.h"
#include "AseraiEngine/Core/EventManager.h"

namespace Aserai
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
