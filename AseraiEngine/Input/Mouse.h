#pragma once

#include "AseraiEngine/Input/InputCodes.h"

#include <queue>

#define MAX_MOUSE_BUTTONS 8

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

	class MouseEvent
	{
	public:
		MouseEvent(MouseEventType type, MousePoint<double> position) : m_Type(type), m_Position(position) {}

		inline MouseEventType GetEventType() const { return m_Type; }
		inline MousePoint<double> GetPosition() const { return m_Position; }
		inline bool IsValid() const { return m_Type != MouseEventType::Invalid; }

	private:
		MouseEventType m_Type;
		MousePoint<double> m_Position;
	};

	class Mouse
	{
	public:
		Mouse();

		bool Init();
		void Destroy();

		void OnMousePressedEvent(MouseCode button, MousePoint<double> position);
		void OnMouseReleasedEvent(MouseCode button, MousePoint<double> position);
		void OnMouseScrollUpEvent(MousePoint<double> position);
		void OnMouseScrollDownEvent(MousePoint<double> position);
		void OnMouseMoveEvent(MousePoint<double> position);

		MouseEvent GetEvent();
		MousePoint<double> GetPosition();

		bool IsButtonDown(MouseCode button) const;
		bool IsEventBufferEmpty() const;

	private:
		bool m_Initialized;
		bool m_ButtonState[MAX_MOUSE_BUTTONS];
		MousePoint<double> m_Position;
		std::queue<MouseEvent> m_EventBuffer;
	};
}
