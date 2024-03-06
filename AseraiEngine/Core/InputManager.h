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

		bool IsKeyPressed(KeyCode key) const;
		bool IsMousePressed(MouseCode button) const;

	private:
		void OnKeyEvent(KeyEventType type, KeyCode key);
		void OnCharEvent(KeyEventType type, unsigned char key);

		void OnMouseButtonEvent(MouseEventType type, MouseCode button, MousePoint<double> position);
		void OnMouseMoveEvent(MousePoint<double> position);
		void OnMouseScrollEvent(MouseEventType type, MousePoint<double> position);

		friend class Window;

	private:
		bool m_Initialized;
		Keyboard m_Keyboard;
		Mouse m_Mouse;
	};
}
