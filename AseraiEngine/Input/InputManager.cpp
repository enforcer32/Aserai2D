#include "AseraiEnginePCH.h"
#include "AseraiEngine/Input/InputManager.h"
#include "AseraiEngine/Core/Engine.h"

#include <GLFW/glfw3.h>

namespace Aserai
{
	bool InputManager::s_Initialized = false;
	bool InputManager::s_MouseScrollState[2] = {};

	bool InputManager::Init()
	{
		if (s_Initialized) return true;

		auto* window = (GLFWwindow*)Engine::Get()->GetWindow().GetNativeWindow();
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				int type = yoffset > 0 ? 1 : 0;
				s_MouseScrollState[type] = 1;
			});

		memset(s_MouseScrollState, 0, sizeof(s_MouseScrollState));
		return s_Initialized = true;
	}

	void InputManager::Destroy()
	{
		s_Initialized = false;
	}

	void InputManager::Reset()
	{
		memset(s_MouseScrollState, 0, sizeof(s_MouseScrollState));
	}

	bool InputManager::IsKeyPressed(KeyCode key)
	{
		auto* window = (GLFWwindow*)Engine::Get()->GetWindow().GetNativeWindow();
		auto state = glfwGetKey(window, key);
		return state == GLFW_PRESS;
	}

	bool InputManager::IsMousePressed(MouseCode button)
	{
		auto* window = (GLFWwindow*)Engine::Get()->GetWindow().GetNativeWindow();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool InputManager::IsMouseScrollingUp()
	{
		return s_MouseScrollState[1];
	}

	bool InputManager::IsMouseScrollingDown()
	{
		return s_MouseScrollState[0];
	}

	glm::vec2 InputManager::GetMousePosition()
	{
		auto* window = (GLFWwindow*)Engine::Get()->GetWindow().GetNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { x, y };
	}
}
