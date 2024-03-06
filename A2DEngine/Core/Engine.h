#pragma once

#include "A2DEngine/Core/Window.h"
#include "A2DEngine/Core/DeltaTime.h"
#include "A2DEngine/Core/EventManager.h"
#include "A2DEngine/Renderer/Renderer2D.h"
#include "A2DEngine/Events/WindowEvents.h"
#include "A2DEngine/ImGui/AImGui.h"

#include <memory>

namespace Aserai2D
{
	struct EngineProperties
	{
		WindowProperties WindowProperties;
	};

	class Engine
	{
	public:
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;
		virtual ~Engine();

		static Engine* Get();
		void Start();
		void Shutdown();
		EngineProperties& GetProperties();
		Window& GetWindow();

		virtual bool OnInit() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnProcessInput() = 0;
		virtual void OnUpdate(DeltaTime dt) = 0;
		virtual void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer) = 0;
		virtual void OnImGuiRender(DeltaTime dt) = 0;

	protected:
		Engine(const EngineProperties& engineProps);
		virtual void OnWindowClose(WindowCloseEvent& ev);
		virtual void OnWindowResize(WindowResizeEvent& ev);

	protected:
		EngineProperties m_Properties;
		std::shared_ptr<EventManager> m_EventManager;
		std::shared_ptr<Renderer2D> m_Renderer2D;

	private:
		static Engine* s_Instance;
		bool m_Initialized, m_Running;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<AImGui> m_ImGui;
	};
}
