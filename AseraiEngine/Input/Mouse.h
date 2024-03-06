#pragma once

#include "AseraiEngine/Input/InputCodes.h"

#define MAX_MOUSE_BUTTONS 8
#define MAX_MOUSE_SCROLLS 2

namespace Aserai
{
	template<typename T>
	struct MousePoint
	{
		T x, y;

		MousePoint() : x(0), y(0) {}
		MousePoint(T x, T y) : x(x), y(y) {}
	};

	enum class MouseEventType
	{
		Invalid,
		Press,
		Release,
		ScrollUp,
		ScrollDown,
		Move,
	};

	class Mouse
	{
	public:
		Mouse();

		bool Init();
		void Destroy();
		void Reset();

		void OnMousePressedEvent(MouseCode button, MousePoint<double> position);
		void OnMouseReleasedEvent(MouseCode button, MousePoint<double> position);
		void OnMouseScrollUpEvent(MousePoint<double> position);
		void OnMouseScrollDownEvent(MousePoint<double> position);
		void OnMouseMoveEvent(MousePoint<double> position);

		MousePoint<double> GetPosition();

		bool IsMousePressed(MouseCode button) const;
		bool IsMouseScrollingUp() const;
		bool IsMouseScrollingDown() const;
		bool IsMouseMoving() const;
		bool IsMouseDragging() const;

	private:
		bool m_Initialized;
		bool m_ButtonState[MAX_MOUSE_BUTTONS];
		bool m_ScrollState[MAX_MOUSE_SCROLLS];
		bool m_Moving;
		MousePoint<double> m_Position;
	};
}
