#pragma once

#include "AseraiEngine/Core/InputManager.h"

#include <string>

struct GLFWwindow;

namespace Aserai
{
	struct WindowProps
	{
		std::string Name;
		uint32_t Width;
		uint32_t Height;
		bool VSync;
	};

	class Window
	{
	public:
		Window();

		bool Init(const WindowProps& props);
		void Destroy();
		void Update();
		
		const WindowProps& GetProperties() const;
		void SetProperties(const WindowProps& props);
		bool IsVSync() const;
		void SetVSync(bool vsync);
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		inline const auto* GetNativeWindow() const { return m_NativeWindow; }

		void SetupInputEvents(const std::shared_ptr<InputManager>& inputManager);

	private:
		bool InitContext();

	private:
		struct WindowPrivateData
		{
			std::shared_ptr<InputManager> InputManager;
		};

		bool m_Initialized;
		WindowProps m_Props;
		GLFWwindow* m_NativeWindow;
		WindowPrivateData m_WinPrivData;
	};
}
