#pragma once

#include "AseraiEngine/Input/InputCodes.h"

#include <queue>

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

	class KeyEvent
	{
	public:
		KeyEvent(KeyEventType type, KeyCode key) : m_Type(type), m_Key(key) {}

		inline KeyCode GetKeyCode() const { return m_Key; }
		inline KeyEventType GetEventType() const { return m_Type; }
		inline bool IsValid() const { return m_Type != KeyEventType::Invalid; }
		inline bool IsPress() const { return m_Type == KeyEventType::Press; }
		inline bool IsRelease() const { return m_Type == KeyEventType::Release; }
		inline bool IsRepeat() const { return m_Type == KeyEventType::Repeat; }

	private:
		KeyEventType m_Type;
		KeyCode m_Key;
	};

	class Keyboard
	{
	public:
		Keyboard();

		bool Init();
		void Destroy();

		void OnKeyPressedEvent(KeyCode key);
		void OnKeyReleasedEvent(KeyCode key);
		void OnCharEvent(unsigned char key);

		KeyEvent GetEvent();
		unsigned char GetChar();

		void SetAutoRepeatKey(bool status);
		void SetAutoRepeatChar(bool status);

		bool IsKeyPressed(KeyCode key) const;
		bool IsKeyBufferEmpty() const;
		bool IsCharBufferEmpty() const;
		bool IsKeyAutoRepeat() const;
		bool IsCharAutoRepeat() const;

	private:
		bool m_Initialized;
		bool m_AutoRepeatKey;
		bool m_AutoRepeatChar;
		bool m_KeyState[MAX_KEYBOARD_KEYS + 1];
		std::queue<KeyEvent> m_KeyBuffer;
		std::queue<unsigned char> m_CharBuffer;
	};
}
