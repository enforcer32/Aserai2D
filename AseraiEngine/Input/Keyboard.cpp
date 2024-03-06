#include "AseraiEnginePCH.h"
#include "AseraiEngine/Input/Keyboard.h"

namespace Aserai
{
	Keyboard::Keyboard()
	{
		m_Initialized = false;
	}

	bool Keyboard::Init()
	{
		memset(m_KeyState, 0, sizeof(m_KeyState));
		m_AutoRepeatKey = true;
		return m_Initialized = true;
	}

	void Keyboard::Destroy()
	{
		m_Initialized = false;
	}

	void Keyboard::Reset()
	{
		//memset(m_KeyState, 0, sizeof(m_KeyState));
	}

	void Keyboard::OnKeyPressedEvent(KeyCode key)
	{
		m_KeyState[key] = true;
	}

	void Keyboard::OnKeyReleasedEvent(KeyCode key)
	{
		m_KeyState[key] = false;
	}

	void Keyboard::SetAutoRepeatKey(bool state)
	{
		m_AutoRepeatKey = state;
	}

	bool Keyboard::IsKeyAutoRepeat() const
	{
		return m_AutoRepeatKey;
	}

	bool Keyboard::IsKeyPressed(KeyCode key) const
	{
		return m_KeyState[key];
	}
}
