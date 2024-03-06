#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>
#include <AseraiEngine/Scene/Scene.h>
#include <AseraiEngine/Utils/AssetManager.h>

#include <AseraiEngine/Components/TransformComponent.h>
#include <AseraiEngine/Components/RigidBodyComponent.h>
#include <AseraiEngine/Components/SpriteComponent.h>
#include <AseraiEngine/Components/CameraComponent.h>
#include <AseraiEngine/Components/KeyboardMovementComponent.h>

#include <imgui.h>

namespace Aserai
{
	class AseraiSandbox : public AseraiApp
	{
	public:
		AseraiSandbox(const WindowProps& windowProps)
			: AseraiApp(windowProps)
		{
			ASERAI_LOG_INFO("Initialized AseraiSandbox");

			m_AssetManager = std::make_shared<AssetManager>();
			m_ActiveScene = std::make_shared<Scene>("Sandbox");

			m_Renderer2D->SetAlphaBlending(true);

			m_InputManager->SetAutoRepeatKey(false);
			m_InputManager->SetAutoRepeatChar(false);
			m_InputManager->SetKeyAutoRepeatHeldDown(false);
			m_InputManager->SetMouseAutoRepeatHeldDown(false);

			Entity camera = m_ActiveScene->CreateEntity();
			camera.AddComponent<CameraComponent>(true);

			Entity player = m_ActiveScene->CreateEntity("player");
			player.AddComponent<TransformComponent>(glm::vec3(-5.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 0.0);
			player.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Spritesheets/top_down_tanks.png"), 2, 2, 1, 7.16, 5.5, 82, 79);
			player.AddComponent<KeyboardMovementComponent>(5.0);
		}

		virtual void OnProcessInput() override
		{
			if (m_InputManager->IsKeyPressed(KeyCode::Escape))
				Shutdown();
		}

		virtual void OnUpdate(DeltaTime dt) override
		{
			m_ActiveScene->OnRuntimeUpdate(dt, m_InputManager, m_EventManager);
		}

		virtual void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer) override
		{
			renderer->ResetRenderStats();
			renderer->SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			renderer->Clear();

			m_ActiveScene->OnRuntimeRender(dt, renderer, m_InputManager);
		}

		virtual void OnImGuiRender(DeltaTime dt) override
		{
			auto& stats = m_Renderer2D->GetRenderStats();
			ImGui::Begin("Stats");
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("DrawCalls: %d", stats.DrawCallCount);
			ImGui::Text("QuadCount: %d", stats.QuadCount);
			ImGui::Text("VertexCount: %d", stats.GetVertexCount());
			ImGui::Text("IndexCount: %d", stats.GetIndexCount());
			ImGui::NewLine();
			ImGui::Text("Scene Stats:");
			ImGui::Text("Active Scene: %s", m_ActiveScene->GetName().c_str());
			ImGui::Text("FPS: %.2f", (1.0f / dt));
			ImGui::End();
		}

		virtual void OnWindowResize(WindowResizeEvent& ev) override
		{
			AseraiApp::OnWindowResize(ev);
			
			m_ActiveScene->OnViewportResize(ev.GetWidth(), ev.GetHeight());
		}

	private:
		std::shared_ptr<AssetManager> m_AssetManager;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiSandbox sandbox({ "AseraiSandbox", 640, 480, true });
	sandbox.Run();
	return 0;
}
