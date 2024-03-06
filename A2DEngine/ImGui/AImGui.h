#pragma once

#include "A2DEngine/Core/Window.h"

namespace Aserai2D
{
	class AImGui
	{
	public:
		AImGui();

		bool Init(const std::unique_ptr<Window>& window);
		void Destroy();

		void BeginFrame();
		void EngFrame();

	private:
		bool m_Initialized;
	};
}
