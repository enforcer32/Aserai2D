#pragma once

#include <stdint.h>

namespace Aserai2D
{
	class Framebuffer
	{
	public:
		Framebuffer(uint32_t width, uint32_t height);
		~Framebuffer();

		void Bind();
		void Unbind();

		uint32_t GetID() const;
		uint32_t GetColorTextureID() const;
		void Resize(uint32_t width, uint32_t height);
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

	private:
		void Reset();

	private:
		uint32_t m_Width, m_Height;
		uint32_t m_FrameBufferID;
		uint32_t m_ColorTextureID;
	};
}
