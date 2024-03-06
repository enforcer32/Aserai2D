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
		memset(m_ButtonState, 0, sizeof(m_ButtonState));
		memset(m_ScrollState, 0, sizeof(m_ScrollState));
		memset(&m_Position, 0, sizeof(m_Position));
		m_Moving = false;
		return m_Initialized = true;
	}

	void Mouse::Destroy()
	{
		m_Initialized = false;
	}

	void Mouse::Reset()
	{
		//memset(m_ButtonState, 0, sizeof(m_ButtonState));
		memset(m_ScrollState, 0, sizeof(m_ScrollState));
		//memset(&m_Position, 0, sizeof(m_Position));
		m_Moving = false;
	}

	void Mouse::OnMousePressedEvent(MouseCode button, MousePoint<double> position)
	{
		m_ButtonState[button] = true;
		m_Position = position;
	}

	void Mouse::OnMouseReleasedEvent(MouseCode button, MousePoint<double> position)
	{
		m_ButtonState[button] = false;
		m_Position = position;
	}

	void Mouse::OnMouseScrollUpEvent(MousePoint<double> position)
	{
		m_ScrollState[1] = true;
		m_Position = position;
	}

	void Mouse::OnMouseScrollDownEvent(MousePoint<double> position)
	{
		m_ScrollState[0] = true;
		m_Position = position;
	}

	void Mouse::OnMouseMoveEvent(MousePoint<double> position)
	{
		m_Position = position;
		m_Moving = true;
	}

	MousePoint<double> Mouse::GetPosition()
	{
		return m_Position;
	}

	bool Mouse::IsMousePressed(MouseCode button) const
	{
		return m_ButtonState[button];
	}

	bool Mouse::IsMouseScrollingUp() const
	{
		return m_ScrollState[1];
	}

	bool Mouse::IsMouseScrollingDown() const
	{
		return m_ScrollState[0];
	}

	bool Mouse::IsMouseMoving() const
	{
		return m_Moving;
	}

	bool Mouse::IsMouseDragging() const
	{
		return (m_ButtonState[MouseCode::Button1] && m_Moving);
	}
}
