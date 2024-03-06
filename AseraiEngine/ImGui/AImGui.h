#pragma once

#include "AseraiEngine/Core/Window.h"

namespace Aserai
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
