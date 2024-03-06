#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>

#include <AseraiEngine/Renderer/Renderer2D.h>

#include <glm/gtc/matrix_transform.hpp>

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
		}

		virtual void OnProcessInput() override
		{
			if (m_InputManager->IsKeyPressed(KeyCode::Escape))
				Shutdown();
		}

		virtual void OnUpdate() override
		{
		}

		virtual void OnRender(std::shared_ptr<Renderer2D>& renderer) override
		{
			renderer->ResetRenderStats();
			
			renderer->SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			renderer->Clear();


			renderer->BeginRenderer();
			//renderer->RenderQuad({ -0.5f, -0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
			//renderer->RenderQuad({ 0.5f, 0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f }, m_BrickWallTexture);
			//renderer->RenderQuad({ 0.5f, 0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f }, m_PantherTankTexture);
		

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
			transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
			//renderer->RenderQuad(transform, { 1.0f, 1.0f, 0.0f, 1.0f });
			renderer->RenderQuad(transform, m_PantherTankTexture);

			//renderer->RenderQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
			renderer->EndRenderer();

			/*std::cout << "DrawCall Count: " << renderer->GetRenderStats().DrawCallCount << std::endl;
			std::cout << "Quad Count: " << renderer->GetRenderStats().QuadCount << std::endl;
			std::cout << "Vertex Count: " << renderer->GetRenderStats().GetVertexCount() << std::endl;
			std::cout << "Index Count: " << renderer->GetRenderStats().GetIndexCount() << std::endl;*/
		}

	private:
		std::shared_ptr<Texture2D> m_BrickWallTexture;
		std::shared_ptr<Texture2D> m_PantherTankTexture;
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiSandbox sandbox({ "AseraiSandbox", 640, 480, true });
	sandbox.Run();
	return 0;
}
