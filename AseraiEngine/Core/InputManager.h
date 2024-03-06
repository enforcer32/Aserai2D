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
		bool IsKeyHeldDown(KeyCode key) const;
		bool IsMousePressed(MouseCode button) const;

		void SetAutoRepeatKey(bool state);
		void SetAutoRepeatChar(bool state);
		void SetKeyAutoRepeatHeldDown(bool state);
		void SetMouseAutoRepeatHeldDown(bool state);

		bool IsKeyAutoRepeat() const;
		bool IsCharAutoRepeat() const;
		bool IsKeyHeldDownAutoRepeat() const;
		bool IsMouseHeldDownAutoRepeat() const;

	private:
		friend class Window;

		void OnKeyEvent(KeyEventType type, KeyCode key);
		void OnCharEvent(KeyEventType type, unsigned char key);

		void OnMouseButtonEvent(MouseEventType type, MouseCode button, MousePoint<double> position);
		void OnMouseMoveEvent(MousePoint<double> position);
		void OnMouseScrollEvent(MouseEventType type, MousePoint<double> position);

	private:
		bool m_Initialized;
		Keyboard m_Keyboard;
		Mouse m_Mouse;
	};
}
