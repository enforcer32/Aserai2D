#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>
#include <AseraiEngine/Scene/Scene.h>

#include <AseraiEngine/Components/RigidBodyComponent.h>

namespace Aserai
{
	class AseraiSandbox : public AseraiApp
	{
	public:
		AseraiSandbox(const WindowProps& windowProps)
			: AseraiApp(windowProps)
		{
			ASERAI_LOG_INFO("Initialized AseraiSandbox");
			m_BrickWallTexture = std::make_shared<Texture2D>("../Assets/Textures/wall_brick.png", true);
			m_PantherTankTexture = std::make_shared<Texture2D>("../Assets/Textures/panther_tank_jlee104.png", true);

			m_Renderer2D->SetAlphaBlending(true);
			m_ActiveScene = std::make_shared<Scene>("Sandbox");

			// Simple Entities
			m_ActiveScene->CreateEntity().AddComponent<RigidBodyComponent>(glm::vec3({ 0.1, 0.0, 0.0 }));
		}

		virtual void OnProcessInput() override
		{
			if (m_InputManager->IsKeyPressed(KeyCode::Escape))
				Shutdown();
		}

		virtual void OnUpdate(DeltaTime dt) override
		{
			ASERAI_LOG_INFO("FPS: {}", (1000 / (dt * 1000)));

			m_ActiveScene->OnRuntimeUpdate(dt);
		}

		virtual void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer) override
		{
			renderer->ResetRenderStats();
			renderer->SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			renderer->Clear();

			m_ActiveScene->OnRuntimeRender(dt, renderer);

			/*std::cout << "DrawCall Count: " << renderer->GetRenderStats().DrawCallCount << std::endl;
			std::cout << "Quad Count: " << renderer->GetRenderStats().QuadCount << std::endl;
			std::cout << "Vertex Count: " << renderer->GetRenderStats().GetVertexCount() << std::endl;
			std::cout << "Index Count: " << renderer->GetRenderStats().GetIndexCount() << std::endl;*/
		}

	private:
		std::shared_ptr<Texture2D> m_BrickWallTexture;
		std::shared_ptr<Texture2D> m_PantherTankTexture;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiSandbox sandbox({ "AseraiSandbox", 640, 480, true });
	sandbox.Run();
	return 0;
}
