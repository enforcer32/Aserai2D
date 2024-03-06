#pragma once

namespace Aserai2D
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const uint32_t* data, uint32_t count, uint32_t usage);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		uint32_t GetSize() const;

	private:
		uint32_t m_BufferID;
		uint32_t m_Size;
	};
}
