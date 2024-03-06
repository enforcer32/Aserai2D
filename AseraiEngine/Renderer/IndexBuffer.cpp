#include "AseraiEnginePCH.h"
#include "AseraiEngine/Renderer/IndexBuffer.h"

#include <glad/glad.h>

namespace Aserai
{
	IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t size, uint32_t usage)
		: m_Size(size)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(*data), data, usage);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t IndexBuffer::GetSize() const
	{
		return m_Size;
	}
}
