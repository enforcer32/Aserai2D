#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>
#include <AseraiEngine/Scene/Scene.h>
#include <AseraiEngine/Utils/AssetManager.h>
#include <AseraiEngine/Utils/FileIO.h>

#include <AseraiEngine/Components/TransformComponent.h>
#include <AseraiEngine/Components/RigidBodyComponent.h>
#include <AseraiEngine/Components/SpriteComponent.h>
#include <AseraiEngine/Components/CameraComponent.h>
#include <AseraiEngine/Components/KeyboardMovementComponent.h>

#include <imgui.h>
#include <sstream>

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

			// Load Tilemap
			LoadLevel();
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
		std::vector<std::string> ParseTilemap(const std::string& filepath)
		{
			std::vector<std::string> tilemap;
			std::string tilemapStr = FileIO::ReadFileContent(filepath);
			std::replace(tilemapStr.begin(), tilemapStr.end(), '\n', ',');

			std::stringstream ss(tilemapStr);
			std::string line;
			while (std::getline(ss, line, ','))
				tilemap.push_back(line);

			return tilemap;
		}

		void LoadLevel()
		{
			Entity camera = m_ActiveScene->CreateEntity("camera");
			SceneCamera sceneCam;
			sceneCam.SetOrthographicSize(19.0f);
			camera.AddComponent<CameraComponent>(sceneCam, true, 10.0);

			std::vector<std::string> tilemap = ParseTilemap("../Assets/Tilemaps/surface.map");

			
			// 03, (C)(X) = 0, (R)(Y) = 3
			double tileScale = 1;
			uint32_t tileSize = 128;
			uint32_t tilemapCols = 25;
			uint32_t tilemapRows = 19; // Index From 1
			
			// each square takes 1 unit (ADD COLLIDER TO THE GRASS)
			uint32_t tileIdx = 0;
			int32_t tilePosX = -(tilemapCols / 2);
			int32_t tilePosY = -(tilemapRows / 2);
			for (uint32_t row = 0; row < tilemapRows; row++)
			{
				for (uint32_t col = 0; col < tilemapCols; col++)
				{
					ASERAI_LOG_INFO("Pos({}, {})", tilePosX, tilePosY);

					std::string tileNum = tilemap[tileIdx++];
					uint32_t x = (tileNum[0] - '0'); // COL 0
					uint32_t y = (tileNum[1] - '0'); // R 3

					Entity tileEntity = m_ActiveScene->CreateEntity();
					tileEntity.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Spritesheets/top_down_tanks.png"), tileSize, tileSize, x, y, 0);
					tileEntity.AddComponent<TransformComponent>(glm::vec3((double)tilePosX, (double)tilePosY, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(tileScale, tileScale, tileScale), 0.0f);
					tilePosX++;
				}
				tilePosX = -(tilemapCols / 2);
				tilePosY++;
			}

			Entity player = m_ActiveScene->CreateEntity("player");
			player.AddComponent<TransformComponent>(glm::vec3(-9.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(2.0, 2.0, 1.0), 90.0f);
			player.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Spritesheets/top_down_tanks.png"), 82, 79, 7.16, 5.5, 0);
			player.AddComponent<KeyboardMovementComponent>(5.0);

			Entity enemy1 = m_ActiveScene->CreateEntity("enemy1");
			enemy1.AddComponent<TransformComponent>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(2.0, 2.0, 1.0), 0.0);
			enemy1.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Spritesheets/top_down_tanks.png"), 82, 79, 6.16, 5.5, 0);
			
			Entity enemy2 = m_ActiveScene->CreateEntity("enemy3");
			enemy2.AddComponent<TransformComponent>(glm::vec3(9.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(2.0, 2.0, 1.0), -90.0f);
			enemy2.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Spritesheets/top_down_tanks.png"), 82, 79, 6.16, 5.5, 0);
		}

	private:
		std::shared_ptr<AssetManager> m_AssetManager;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiTankGame2D tankgame2d({ "AseraiTankGame2D", 800, 600, true });
	tankgame2d.Run();
	return 0;
}
