#include "A2DEditorPCH.h"

#include "A2DEditor/Panels/PanelManager.h"
#include "A2DEditor/Panels/SceneGraphPanel.h"
#include "A2DEditor/Panels/EntityPropertiesPanel.h"
#include "A2DEditor/Panels/AssetManagerPanel.h"

#include <A2DEngine/Asset/AssetManager.h>
#include <A2DEngine/Core/Engine.h>
#include <A2DEngine/Core/Logger.h>
#include <A2DEngine/Scene/Scene.h>
#include <A2DEngine/Renderer/Framebuffer.h>
#include <A2DEngine/Editor/EditorCamera.h>
#include <A2DEngine/Input/InputManager.h>

#include <A2DEngine/Components/TransformComponent.h>
#include <A2DEngine/Components/SpriteComponent.h>
#include <A2DEngine/Components/CameraComponent.h>
#include <A2DEngine/Components/KeyboardMovementComponent.h>

#include <A2DEngine/Asset/TextureAsset.h>
#include <A2DEngine/Asset/SpritesheetAsset.h>

#include <imgui.h>
#include <glm/glm.hpp>

namespace Aserai2D
{
	class A2DEditor : public Engine
	{
	public:
		A2DEditor(const EngineProperties& engineProps)
			: Engine(engineProps)
		{
		}

		virtual bool OnInit() override
		{
			ASERAI_LOG_INFO("Initializing A2DEditor");

			if (!AssetManager::OnInit()) // Per Project or Engine.h?
				ASERAI_LOG_CRITICAL("Failed to Initialize Asset Manager");

			m_ActiveScene = std::make_shared<Scene>("Editor");
			m_Framebuffer = std::make_shared<Framebuffer>(m_Properties.WindowProperties.Width, m_Properties.WindowProperties.Height);
			m_EditorCamera = std::make_shared<EditorCamera>();
			m_PanelManager = std::make_shared<PanelManager>();

			m_Renderer2D->SetAlphaBlending(true);
			m_Renderer2D->SetLineWidth(2.0f);

			m_PanelManager->AddPanel("SceneGraph", std::make_shared<SceneGraphPanel>(m_ActiveScene));
			m_PanelManager->AddPanel("EntityProperties", std::make_shared<EntityPropertiesPanel>());
			m_PanelManager->AddPanel("AssetManager", std::make_shared<AssetManagerPanel>(m_ActiveScene)); // On SwitchScene Switch Scene Argument from Panels

			// TMP
			auto tankTextureID = AssetManager::CreateAsset<TextureAsset>("../Assets/Spritesheets/top_down_tanks.png");
			auto spriteSheetID = AssetManager::CreateAsset<SpritesheetAsset>(tankTextureID, 128, 128, 32, 0);
			auto& spriteAsset = AssetManager::GetAsset<SpritesheetAsset>(spriteSheetID);

			Entity player = m_ActiveScene->CreateEntity("player");
			player.AddComponent<TransformComponent>(glm::vec3(-5.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 0.0);
			//player.AddComponent<SpriteComponent>(tankTextureID, 2, 2, 1); // DONT ADD TEXTURE USING NAME, LOOP OVER TEXTURES OR ADD USING CONTENT BROWSER
			player.AddComponent<SpriteComponent>(spriteAsset->GetSprite(8).Texture, 2, 2, 1, spriteAsset->GetSprite(8).TextureUV);
			//player.AddComponent<KeyboardMovementComponent>(5.0, true);

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
			if (m_Viewport.x > 0.0f && m_Viewport.y > 0.0f && (m_Framebuffer->GetWidth() != m_Viewport.x || m_Framebuffer->GetHeight() != m_Viewport.y))
			{
				m_Framebuffer->Resize(m_Viewport.x, m_Viewport.y);
				m_ActiveScene->OnViewportResize(m_Viewport.x, m_Viewport.y);
				m_EditorCamera->SetViewport(m_Viewport.x, m_Viewport.y);
			}

			if (m_ViewportFocused)
				m_EditorCamera->OnUpdate(dt);

			m_ActiveScene->OnEditorUpdate(dt, m_EventManager);
		}

		virtual void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer) override
		{
			m_Framebuffer->Bind();
			renderer->ResetRenderStats();
			renderer->SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			renderer->Clear();

			m_ActiveScene->OnEditorRender(dt, renderer, m_EditorCamera);
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
			ImGui::Text("LineCount: %d", stats.LineCount);
			ImGui::Text("QuadVertexCount: %d", stats.GetQuadVertexCount());
			ImGui::Text("QuadIndexCount: %d", stats.GetQuadIndexCount());
			ImGui::Text("LineVertexCount: %d", stats.GetLineVertexCount());
			ImGui::Text("LineIndexCount: %d", stats.GetLineIndexCount());
			ImGui::NewLine();
			ImGui::Text("Scene Stats:");
			ImGui::Text("Active Scene: %s", m_ActiveScene->GetName().c_str());
			ImGui::Text("FPS: %.2f", (1.0f / dt));
			ImGui::End();
		}

		virtual void OnWindowResize(WindowResizeEvent& ev) override
		{
			Engine::OnWindowResize(ev);
			m_ActiveScene->OnViewportResize(ev.GetWidth(), ev.GetHeight());
		}

	private:
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
	Aserai2D::EngineProperties engineProps;
	engineProps.WindowProperties = { "A2DEditor", 1920, 1080, true };
	Aserai2D::A2DEditor editor(engineProps);
	editor.Start();
	return 0;
}
