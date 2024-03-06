#include "AseraiEnginePCH.h"
#include "AseraiEngine/Renderer/Render.h"

#include <glad/glad.h>

namespace Aserai
{
	void Render::DrawIndexed(uint32_t drawType, const VertexArray& va, uint32_t count)
	{
		va.Bind();
		glDrawElements(drawType, count == 0 ? va.GetIndexBuffer()->GetSize() : count, GL_UNSIGNED_INT, nullptr);
	}
}
