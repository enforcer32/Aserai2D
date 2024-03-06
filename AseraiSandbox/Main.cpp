#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>

namespace Aserai
{
	class AseraiSandbox : public AseraiApp
	{
	public:
		AseraiSandbox(const WindowProps& windowProps)
			: AseraiApp(windowProps)
		{
			ASERAI_LOG_INFO("Initialized AseraiSandbox");
		}

		virtual void OnProcessInput() override
		{
		}

		virtual void OnUpdate() override
		{
		}

		virtual void OnRender() override
		{
		}
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiSandbox sandbox({ "AseraiSandbox", 640, 480, true });
	sandbox.Run();
	sandbox.Shutdown();
	return 0;
}
