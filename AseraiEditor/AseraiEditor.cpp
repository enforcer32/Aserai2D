#include "AseraiEditorPCH.h"

#include "AseraiEditor/Panels/PanelManager.h"
#include "AseraiEditor/Panels/SceneGraphPanel.h"
#include "AseraiEditor/Panels/EntityPropertiesPanel.h"

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>
#include <AseraiEngine/Utils/AssetManager.h>
#include <AseraiEngine/Scene/Scene.h>
#include <AseraiEngine/Renderer/Framebuffer.h>
#include <AseraiEngine/Scene/EditorCamera.h>

#include <AseraiEngine/Components/TransformComponent.h>
#include <AseraiEngine/Components/SpriteComponent.h>
#include <AseraiEngine/Components/CameraComponent.h>
#include <AseraiEngine/Components/KeyboardMovementComponent.h>

#include <imgui.h>
#include <glm/glm.hpp>

namespace Aserai
{
	class AseraiEditor : public AseraiApp
	{
	public:
		AseraiEditor(const WindowProps& windowProps)
			: AseraiApp(windowProps)
		{
			ASERAI_LOG_INFO("Initialized AseraiEditor");

			m_AssetManager = std::make_shared<AssetManager>();
			m_ActiveScene = std::make_shared<Scene>("Editor");
			m_Framebuffer = std::make_shared<Framebuffer>(windowProps.Width, windowProps.Height);
			m_EditorCamera = std::make_shared<EditorCamera>();
			m_PanelManager = std::make_shared<PanelManager>();

			m_Renderer2D->SetAlphaBlending(true);

			m_InputManager->SetAutoRepeatKey(false);
			m_InputManager->SetAutoRepeatChar(false);
			m_InputManager->SetKeyAutoRepeatHeldDown(false);
			m_InputManager->SetMouseAutoRepeatHeldDown(false);

			m_PanelManager->AddPanel("SceneGraph", std::make_shared<SceneGraphPanel>(m_ActiveScene, m_InputManager));
			m_PanelManager->AddPanel("Entity Properties", std::make_shared<EntityPropertiesPanel>());

			// TMP
			Entity player = m_ActiveScene->CreateEntity("player");
			player.AddComponent<TransformComponent>(glm::vec3(-5.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 0.0);
			player.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Spritesheets/top_down_tanks.png"), 2, 2, 1, 7.16, 5.5, 82, 79);
			//player.AddComponent<KeyboardMovementComponent>(5.0, true);
		}

		virtual void OnProcessInput() override
		{
			if (m_InputManager->IsKeyPressed(KeyCode::Escape))
				Shutdown();
		}

		virtual void OnUpdate(DeltaTime dt) override
		{
			if (m_Viewport.x > 0.0f && m_Viewport.y > 0.0f && (m_Framebuffer->GetWidth() != m_Viewport.x || m_Framebuffer->GetHeight() != m_Viewport.y))
			{
				m_Framebuffer->Resize(m_Viewport.x, m_Viewport.y);
				m_ActiveScene->OnViewportResize(m_Viewport.x, m_Viewport.y);
				m_EditorCamera->SetViewport(m_Viewport.x, m_Viewport.y);
			}

			if (m_ViewportFocused)
				m_EditorCamera->OnUpdate(dt, m_InputManager);

			m_ActiveScene->OnEditorUpdate(dt, m_InputManager, m_EventManager);
		}

		virtual void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer) override
		{
			m_Framebuffer->Bind();
			renderer->ResetRenderStats();
			renderer->SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			renderer->Clear();

			m_ActiveScene->OnEditorRender(dt, renderer, m_InputManager, m_EditorCamera);
			m_Framebuffer->Unbind();
		}

		virtual void OnImGuiRender(DeltaTime dt) override
		{
			static bool dockspace_open = true;
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::Begin("DockSpace", &dockspace_open, window_flags);

			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{

					if (ImGui::MenuItem("Exit"))
						Shutdown();

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			m_PanelManager->RenderAllPanels();
			
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
			m_ViewportFocused = ImGui::IsWindowFocused();
			m_ActiveScene->SetViewportFocus(m_ViewportFocused);
			ImVec2 viewport = ImGui::GetContentRegionAvail();
			m_Viewport = { viewport.x, viewport.y };
			ImGui::Image((void*)m_Framebuffer->GetColorTextureID(), ImVec2(m_Viewport.x, m_Viewport.y), ImVec2(0, 1), ImVec2(1, 0));
			
			ImGui::End();
			ImGui::PopStyleVar();
			ImGui::End();

			auto& stats = m_Renderer2D->GetRenderStats();
			ImGui::Begin("Performance");
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
		std::shared_ptr<Framebuffer> m_Framebuffer;
		std::shared_ptr<EditorCamera> m_EditorCamera;
		std::shared_ptr<PanelManager> m_PanelManager;
		bool m_ViewportFocused;
		glm::vec2 m_Viewport;
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiEditor editor({ "AseraiEditor", 1920, 1080, true });
	editor.Run();
	return 0;
}
