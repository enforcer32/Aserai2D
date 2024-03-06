#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>
#include <AseraiEngine/Scene/Scene.h>
#include <AseraiEngine/Utils/AssetManager.h>

#include <AseraiEngine/Components/TransformComponent.h>
#include <AseraiEngine/Components/RigidBodyComponent.h>
#include <AseraiEngine/Components/SpriteComponent.h>
#include <AseraiEngine/Components/CameraComponent.h>

#include <imgui.h>

namespace Aserai
{
	class AseraiTankGame2D : public AseraiApp
	{
	public:
		AseraiTankGame2D(const WindowProps& windowProps)
			: AseraiApp(windowProps)
		{
			ASERAI_LOG_INFO("Initialized AseraiTankGame2D");

			m_AssetManager = std::make_shared<AssetManager>();

			m_Renderer2D->SetAlphaBlending(true);
			m_ActiveScene = std::make_shared<Scene>("TankGame2D");
		}

		virtual void OnProcessInput() override
		{
			if (m_InputManager->IsKeyPressed(KeyCode::Escape))
				Shutdown();
		}

		virtual void OnUpdate(DeltaTime dt) override
		{
			m_ActiveScene->OnRuntimeUpdate(dt, m_InputManager);
		}

		virtual void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer) override
		{
			renderer->ResetRenderStats();
			renderer->SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			renderer->Clear();

			m_ActiveScene->OnRuntimeRender(dt, renderer);
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
	Aserai::AseraiTankGame2D tankgame2d({ "AseraiTankGame2D", 640, 480, true });
	tankgame2d.Run();
	return 0;
}
