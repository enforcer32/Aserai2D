#pragma once

#include "AseraiEngine/Renderer/VertexBufferLayout.h"

namespace Aserai
{
	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size, uint32_t usage);
		VertexBuffer(const void* data, uint32_t size, uint32_t usage);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
		void SetBuffer(const void* data, uint32_t size);

		const VertexBufferLayout& GetLayout() const;
		void SetLayout(const VertexBufferLayout& layout);

	private:
		uint32_t m_BufferID;
		VertexBufferLayout m_Layout;
	};
}
