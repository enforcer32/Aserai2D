#pragma once

#include "AseraiEngine/Core/Window.h"

#include <memory>

namespace Aserai
{
	class AseraiApp
	{
	public:
		AseraiApp(const WindowProps& windowProps);
		virtual ~AseraiApp() = default;

		void Run();
		void Shutdown();

		virtual void OnProcessInput() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;

	private:
		bool m_Running;
		std::unique_ptr<Window> m_Window;
	};
}
