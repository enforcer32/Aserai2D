#include "AseraiEnginePCH.h"
#include "AseraiEngine/Core/AseraiApp.h"
#include "AseraiEngine/Core/Logger.h"
#include "AseraiEngine/Core/DeltaTime.h"
#include "AseraiEngine/Utils/DateTime.h"

namespace Aserai
{
	AseraiApp::AseraiApp(const WindowProps& windowProps)
	{
		Logger::Init();

		m_Window = std::make_unique<Window>();
		if (!m_Window->Init(windowProps))
			ASERAI_LOG_CRITICAL("Failed to Initialize Window");

		m_InputManager = std::make_shared<InputManager>();
		if(!m_InputManager->Init())
			ASERAI_LOG_CRITICAL("Failed to Initialize InputManager");

		m_Window->SetupInputEvents(m_InputManager);

		m_Renderer2D = std::make_shared<Renderer2D>();
		if (!m_Renderer2D->Init(1000))
			ASERAI_LOG_CRITICAL("Failed to Initialize Renderer2D");

		m_Initialized = true;
		m_Running = true;
	}

	AseraiApp::~AseraiApp()
	{
		if (m_Initialized)
		{
			m_Renderer2D->Destroy();
			m_InputManager->Destroy();
			m_Window->Destroy();
		}
	}

	void AseraiApp::Run()
	{
		DeltaTime lastDelteTime = 0.0;

		while (m_Running)
		{
			DeltaTime time = DateTime::GetTimeSeconds();
			DeltaTime dt = time - lastDelteTime;
			lastDelteTime = time;

			if (dt > 0)
			{
				OnProcessInput();
				OnUpdate();
				OnRender(m_Renderer2D);
			}

			m_Window->Update();
		}
	}

	void AseraiApp::Shutdown()
	{
		m_Running = false;
	}
}
