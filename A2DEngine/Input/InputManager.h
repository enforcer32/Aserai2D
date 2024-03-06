#pragma once

#include "A2DEngine/Input/InputCodes.h"

#include <glm/glm.hpp>

namespace Aserai2D
{
	class InputManager
	{
	public:
		// Keyboard
		static bool IsKeyPressed(KeyCode key);

		// Mouse
		static bool IsMousePressed(MouseCode button);
		static bool IsMouseScrollingUp();
		static bool IsMouseScrollingDown();
		static glm::vec2 GetMousePosition();

	private:
		friend class Engine;
		static bool Init();
		static void Destroy();
		static void Reset();

	private:
		static bool s_Initialized;
		static bool s_MouseScrollState[2];
	};
}
