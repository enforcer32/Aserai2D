#pragma once

#include "A2DEngine/Renderer/VertexArray.h"

namespace Aserai2D
{
	class Render
	{
	public:
		static void DrawIndexed(uint32_t drawMode, const VertexArray& va, uint32_t count = 0);
	};
}
