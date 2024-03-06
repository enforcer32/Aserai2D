#pragma once

#include "AseraiEngine/Core/Window.h"
#include "AseraiEngine/Core/EventManager.h"
#include "AseraiEngine/Core/InputManager.h"
#include "AseraiEngine/Renderer/Renderer2D.h"
#include "AseraiEngine/Events/WindowEvents.h"

#include <memory>

namespace Aserai
{
	class AseraiApp
	{
	public:
		AseraiApp(const WindowProps& windowProps);
		virtual ~AseraiApp();

		void Run();
		void Shutdown();

		virtual void OnProcessInput() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender(std::shared_ptr<Renderer2D>& renderer) = 0;

	protected:
		std::shared_ptr<EventManager> m_EventManager;
		std::shared_ptr<InputManager> m_InputManager;
		std::shared_ptr<Renderer2D> m_Renderer2D;

	protected:
		virtual void OnWindowClose(WindowCloseEvent& ev);
		virtual void OnWindowResize(WindowResizeEvent& ev);

	private:
		bool m_Initialized, m_Running;
		std::unique_ptr<Window> m_Window;
	};
}
