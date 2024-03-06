#include "A2DSandboxPCH.h"

#include <A2DEngine/Core/Engine.h>
#include <A2DEngine/Core/Logger.h>
#include <A2DEngine/Scene/Scene.h>
#include <A2DEngine/Input/InputManager.h>

#include <imgui.h>

namespace Aserai2D
{
	class A2DSandbox : public Engine
	{
	public:
		A2DSandbox(const EngineProperties& engineProps)
			: Engine(engineProps)
		{
		}

		virtual bool OnInit() override
		{
			ASERAI_LOG_INFO("Initializing AseraiSandbox");
			m_ActiveScene = std::make_shared<Scene>("Sandbox");
			return true;
		}

		virtual void OnDestroy() override
		{

		}

		virtual void OnProcessInput() override
		{
			if (InputManager::IsKeyPressed(KeyCode::Escape))
				Shutdown();
		}

		virtual void OnUpdate(DeltaTime dt) override
		{
			m_ActiveScene->OnRuntimeUpdate(dt, m_EventManager);
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
			/*auto& stats = m_Renderer2D->GetRenderStats();
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
			ImGui::End();*/
		}

		virtual void OnWindowResize(WindowResizeEvent& ev) override
		{
			Engine::OnWindowResize(ev);
			m_ActiveScene->OnViewportResize(ev.GetWidth(), ev.GetHeight());
		}

	private:
		std::shared_ptr<Scene> m_ActiveScene;
	};
}

int main(int argc, char* argv)
{
	Aserai2D::EngineProperties engineProps;
	engineProps.WindowProperties = { "AseraiSandbox", 640, 480, true };
	Aserai2D::A2DSandbox sandbox(engineProps);
	sandbox.Start();
	return 0;
}
