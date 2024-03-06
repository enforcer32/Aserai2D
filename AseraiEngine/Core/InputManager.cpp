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

	bool InputManager::IsKeyPressed(KeyCode key) const
	{
		return m_Keyboard.IsKeyPressed(key);
	}

	bool InputManager::IsMousePressed(MouseCode button) const
	{
		return m_Mouse.IsButtonDown(button);
	}

	void InputManager::SetAutoRepeatKey(bool status)
	{
		m_Keyboard.SetAutoRepeatKey(status);
	}

	void InputManager::SetAutoRepeatChar(bool status)
	{
		m_Keyboard.SetAutoRepeatChar(status);
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

	void InputManager::OnCharEvent(KeyEventType type, unsigned char key)
	{
		switch (type)
		{
		case KeyEventType::Press:
			m_Keyboard.OnCharEvent(key);
			break;
		case KeyEventType::Repeat:
			if (m_Keyboard.IsCharAutoRepeat())
				m_Keyboard.OnCharEvent(key);
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
