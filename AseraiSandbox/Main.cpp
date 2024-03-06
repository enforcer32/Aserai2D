#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>

#include <AseraiEngine/Renderer/Renderer2D.h>

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
		}

		virtual void OnProcessInput() override
		{
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
			renderer->RenderQuad({ -0.5f, -0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
			renderer->RenderQuad({ 0.5f, 0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f }, m_BrickWallTexture);
			renderer->EndRenderer();

			/*std::cout << "DrawCall Count: " << renderer->GetRenderStats().DrawCallCount << std::endl;
			std::cout << "Quad Count: " << renderer->GetRenderStats().QuadCount << std::endl;
			std::cout << "Vertex Count: " << renderer->GetRenderStats().GetVertexCount() << std::endl;
			std::cout << "Index Count: " << renderer->GetRenderStats().GetIndexCount() << std::endl;*/
		}

	private:
		std::shared_ptr<Texture2D> m_BrickWallTexture;
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiSandbox sandbox({ "AseraiSandbox", 640, 480, true });
	sandbox.Run();
	sandbox.Shutdown();
	return 0;
}
