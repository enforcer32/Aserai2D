#pragma once

#include "AseraiEngine/Renderer/VertexArray.h"

namespace Aserai
{
	#define GL_TRIANGLES 0x0004

	class Render
	{
	public:
		static void DrawIndexed(uint32_t drawType, const VertexArray& va, uint32_t count = 0);
	};
}
