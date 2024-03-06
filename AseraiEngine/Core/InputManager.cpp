#include "AseraiEnginePCH.h"
#include "AseraiEngine/Core/InputManager.h"

namespace Aserai
{
	InputManager::InputManager()
	{
		m_Initialized = false;
	}

	bool InputManager::Init()
	{
		if (!m_Keyboard.Init()) return false;
		if (!m_Mouse.Init()) return false;
		return m_Initialized = true;
	}

	void InputManager::Destroy()
	{
		if (m_Initialized)
		{
			m_Keyboard.Destroy();
			m_Mouse.Destroy();
			m_Initialized = false;
		}
	}

	void InputManager::Reset()
	{
		m_Keyboard.Reset();
		m_Mouse.Reset();
	}

	bool InputManager::IsKeyPressed(KeyCode key) const
	{
		return m_Keyboard.IsKeyPressed(key);
	}

	void InputManager::SetAutoRepeatKey(bool state)
	{
		m_Keyboard.SetAutoRepeatKey(state);
	}

	bool InputManager::IsKeyAutoRepeat() const
	{
		return m_Keyboard.IsKeyAutoRepeat();
	}

	bool InputManager::IsMousePressed(MouseCode button) const
	{
		return m_Mouse.IsMousePressed(button);
	}

	bool InputManager::IsMouseScrollingUp() const
	{
		return m_Mouse.IsMouseScrollingUp();
	}

	bool InputManager::IsMouseScrollingDown() const
	{
		return m_Mouse.IsMouseScrollingDown();
	}

	bool InputManager::IsMouseMoving() const
	{
		return m_Mouse.IsMouseMoving();
	}
	
	bool InputManager::IsMouseDragging() const
	{
		return m_Mouse.IsMouseDragging();
	}

	void InputManager::OnKeyEvent(KeyEventType type, KeyCode key)
	{
		switch (type)
		{
		case KeyEventType::Press:
			m_Keyboard.OnKeyPressedEvent(key);
			break;
		case KeyEventType::Release:
			m_Keyboard.OnKeyReleasedEvent(key);
			break;
		case KeyEventType::Repeat:
			if (m_Keyboard.IsKeyAutoRepeat())
				m_Keyboard.OnKeyPressedEvent(key);
			break;
		default:
			break;
		}
	}

	void InputManager::OnMouseButtonEvent(MouseEventType type, MouseCode button, MousePoint<double> position)
	{
		switch (type)
		{
		case MouseEventType::Press:
			m_Mouse.OnMousePressedEvent(button, position);
			break;
		case MouseEventType::Release:
			m_Mouse.OnMouseReleasedEvent(button, position);
			break;
		default:
			break;
		}
	}

	void InputManager::OnMouseMoveEvent(MousePoint<double> position)
	{
		m_Mouse.OnMouseMoveEvent(position);
	}

	void InputManager::OnMouseScrollEvent(MouseEventType type, MousePoint<double> position)
	{
		switch (type)
		{
		case MouseEventType::ScrollUp:
			m_Mouse.OnMouseScrollUpEvent(position);
			break;
		case MouseEventType::ScrollDown:
			m_Mouse.OnMouseScrollDownEvent(position);
			break;
		default:
			break;
		}
	}
}
