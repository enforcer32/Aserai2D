#include "AseraiEnginePCH.h"
#include "AseraiEngine/Renderer/VertexBuffer.h"

#include <glad/glad.h>

namespace Aserai
{
	VertexBuffer::VertexBuffer(uint32_t size, uint32_t usage)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage);
	}

	VertexBuffer::VertexBuffer(const void* data, uint32_t size, uint32_t usage)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetBuffer(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	const VertexBufferLayout& VertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	void VertexBuffer::SetLayout(const VertexBufferLayout& layout)
	{
		m_Layout = layout;
	}
}
