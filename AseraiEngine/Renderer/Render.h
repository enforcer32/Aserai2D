#pragma once

#include "AseraiEngine/Renderer/VertexArray.h"

namespace Aserai
{
	class Render
	{
	public:
		static void DrawIndexed(uint32_t drawMode, const VertexArray& va, uint32_t count = 0);
	};
}
