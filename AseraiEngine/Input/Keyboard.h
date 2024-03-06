#pragma once

#include "AseraiEngine/Input/InputCodes.h"

#define MAX_KEYBOARD_KEYS 348

namespace Aserai
{
	enum class KeyEventType
	{
		Invalid,
		Press,
		Release,
		Repeat,
	};

	class Keyboard
	{
	public:
		Keyboard();

		bool Init();
		void Destroy();
		void Reset();

		void OnKeyPressedEvent(KeyCode key);
		void OnKeyReleasedEvent(KeyCode key);

		void SetAutoRepeatKey(bool state);
		bool IsKeyAutoRepeat() const;
		bool IsKeyPressed(KeyCode key) const;

	private:
		bool m_Initialized;
		bool m_AutoRepeatKey;
		bool m_KeyState[MAX_KEYBOARD_KEYS + 1];
	};
}
