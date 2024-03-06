#include "A2DEnginePCH.h"
#include "A2DEngine/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace Aserai2D
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)
	{
		glBindVertexArray(m_ArrayID);
		vb->Bind();

		for (int i = 0; i < vb->GetLayout().GetAttributes().size(); i++)
		{
			auto& attrib = vb->GetLayout().GetAttributes()[i];
			glVertexAttribPointer(i, attrib.Size, ConvertShaderDataTypeToGLType(attrib.Type), attrib.Normalized, vb->GetLayout().GetStride(), (const void*)attrib.Offset);
			glEnableVertexAttribArray(i);
		}

		m_VertexBuffers.push_back(vb);
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
	{
		glBindVertexArray(m_ArrayID);
		ib->Bind();
		m_IndexBuffer = ib;
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& VertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}
