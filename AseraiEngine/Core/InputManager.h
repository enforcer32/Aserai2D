#pragma once

#include "AseraiEngine/Input/Keyboard.h"
#include "AseraiEngine/Input/Mouse.h"

namespace Aserai
{
	class InputManager
	{
	public:
		InputManager();

		bool Init();
		void Destroy();
		void Reset();

		// Keyboard
		bool IsKeyPressed(KeyCode key) const;
		void SetAutoRepeatKey(bool state);
		bool IsKeyAutoRepeat() const;

		// Mouse
		bool IsMousePressed(MouseCode button) const;
		bool IsMouseScrollingUp() const;
		bool IsMouseScrollingDown() const;
		bool IsMouseMoving() const;
		bool IsMouseDragging() const;
		MousePoint<double> GetPosition();

	private:
		friend class Window;

		void OnKeyEvent(KeyEventType type, KeyCode key);

		void OnMouseButtonEvent(MouseEventType type, MouseCode button, MousePoint<double> position);
		void OnMouseMoveEvent(MousePoint<double> position);
		void OnMouseScrollEvent(MouseEventType type, MousePoint<double> position);

	private:
		bool m_Initialized;
		Keyboard m_Keyboard;
		Mouse m_Mouse;
	};
}
