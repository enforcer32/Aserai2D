#include "A2DEnginePCH.h"
#include "A2DEngine/Renderer/Render.h"

#include <glad/glad.h>

namespace Aserai2D
{
	void Render::DrawIndexed(uint32_t drawMode, const VertexArray& va, uint32_t count)
	{
		va.Bind();
		glDrawElements(drawMode, count == 0 ? va.GetIndexBuffer()->GetSize() : count, GL_UNSIGNED_INT, nullptr);
	}
}
