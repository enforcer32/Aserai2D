#include "AseraiEnginePCH.h"
#include "AseraiEngine/Input/Mouse.h"

namespace Aserai
{
	Mouse::Mouse()
	{
		m_Initialized = false;
	}

	bool Mouse::Init()
	{
		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			m_ButtonState[i] = false;
			m_OldButtonState[i] = false;
		}

		m_AutoRepeatHeldDown = true;
		return m_Initialized = true;
	}

	void Mouse::Destroy()
	{
		m_Initialized = false;
	}

	void Mouse::OnMousePressedEvent(MouseCode button, MousePoint<double> position)
	{
		m_ButtonState[button] = true;
		m_EventBuffer.push(MouseEvent(MouseEventType::Press, position));
	}

	void Mouse::OnMouseReleasedEvent(MouseCode button, MousePoint<double> position)
	{
		m_ButtonState[button] = false;
		m_EventBuffer.push(MouseEvent(MouseEventType::Release, position));
	}

	void Mouse::OnMouseScrollUpEvent(MousePoint<double> position)
	{
		m_EventBuffer.push(MouseEvent(MouseEventType::ScrollUp, position));
	}

	void Mouse::OnMouseScrollDownEvent(MousePoint<double> position)
	{
		m_EventBuffer.push(MouseEvent(MouseEventType::ScrollDown, position));
	}

	void Mouse::OnMouseMoveEvent(MousePoint<double> position)
	{
		m_Position = position;
		m_EventBuffer.push(MouseEvent(MouseEventType::Move, position));
	}

	MouseEvent Mouse::GetEvent()
	{
		if (!m_EventBuffer.empty())
		{
			MouseEvent ev = m_EventBuffer.front();
			m_EventBuffer.pop();
			return ev;
		}

		return { MouseEventType::Invalid, {0, 0} };
	}

	MousePoint<double> Mouse::GetPosition()
	{
		return m_Position;
	}

	void Mouse::SetAutoRepeatHeldDown(bool state)
	{
		m_AutoRepeatHeldDown = state;
	}

	bool Mouse::IsButtonDown(MouseCode button) const
	{
		return m_ButtonState[button];
	}

	bool Mouse::IsEventBufferEmpty() const
	{
		return m_EventBuffer.empty();
	}

	bool Mouse::IsHeldDownAutoRepeat() const
	{
		return m_AutoRepeatHeldDown;
	}

	bool Mouse::WasButtonDown(MouseCode button) const
	{
		return m_OldButtonState[button];
	}

	void Mouse::SetButtonState(MouseCode button, bool state) const
	{
		m_ButtonState[button] = state;
	}
	
	void Mouse::SetOldButtonState(MouseCode button, bool state) const
	{
		m_OldButtonState[button] = state;
	}
}
