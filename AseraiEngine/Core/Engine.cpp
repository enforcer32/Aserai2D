#include "AseraiEnginePCH.h"
#include "AseraiEngine/Core/Engine.h"
#include "AseraiEngine/Core/Logger.h"
#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Utils/DateTime.h"
#include "AseraiEngine/Core/Assertion.h"

namespace Aserai
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine(const EngineProperties& engineProps)
	{
		ASERAI_ASSERT(!s_Instance, "ENGINE ALREADY INITIALIZED");
		s_Instance = this;
		m_Properties = engineProps;

		Logger::Init();

		m_Window = std::make_unique<Window>();
		if (!m_Window->Init(m_Properties.WindowProperties))
			ASERAI_LOG_CRITICAL("Failed to Initialize Window");

		m_EventManager = std::make_shared<EventManager>();
		if (!m_EventManager->Init())
			ASERAI_LOG_CRITICAL("Failed to Initialize EventManager");

		m_InputManager = std::make_shared<InputManager>();
		if(!m_InputManager->Init())
			ASERAI_LOG_CRITICAL("Failed to Initialize InputManager");

		m_Window->SetupWindowEvents(m_EventManager);
		m_Window->SetupInputEvents(m_InputManager);

		m_EventManager->Subscribe<WindowCloseEvent>(this, &Engine::OnWindowClose);
		m_EventManager->Subscribe<WindowResizeEvent>(this, &Engine::OnWindowResize);

		m_Renderer2D = std::make_shared<Renderer2D>();
		if (!m_Renderer2D->Init(1000))
			ASERAI_LOG_CRITICAL("Failed to Initialize Renderer2D");

		m_ImGui = std::make_unique<AImGui>();
		if(!m_ImGui->Init(m_Window))
			ASERAI_LOG_CRITICAL("Failed to Initialize AImGui");
	}

	Engine::~Engine()
	{
		if (m_Initialized)
		{
			m_ImGui->Destroy();
			m_Renderer2D->Destroy();
			m_InputManager->Destroy();
			m_EventManager->Destroy();
			m_Window->Destroy();
		}
	}

	Engine* Engine::Get()
	{
		return s_Instance;
	}

	void Engine::Start()
	{
		if (!OnInit())
			ASERAI_LOG_CRITICAL("Engine OnInit Failed");

		m_Initialized = true;
		m_Running = true;

		DeltaTime lastDelteTime = 0.0;

		while (m_Running)
		{
			DeltaTime time = DateTime::GetTimeSeconds();
			DeltaTime dt = time - lastDelteTime;
			lastDelteTime = time;

			if (dt > 0)
			{
				OnProcessInput();
				OnUpdate(dt);
				OnRender(dt, m_Renderer2D);

				m_ImGui->BeginFrame();
				OnImGuiRender(dt);
				m_ImGui->EngFrame();
			}

			m_InputManager->Reset();
			m_Window->Update();
		}

		OnDestroy();
	}

	void Engine::Shutdown()
	{
		m_Running = false;
	}

	EngineProperties& Engine::GetProperties()
	{
		return m_Properties;
	}

	Window& Engine::GetWindow()
	{
		return *m_Window;
	}

	void Engine::OnWindowClose(WindowCloseEvent& ev)
	{
		Shutdown();
	}

	void Engine::OnWindowResize(WindowResizeEvent& ev)
	{
		m_Renderer2D->SetViewPort(0, 0, ev.GetWidth(), ev.GetHeight());
	}
}
