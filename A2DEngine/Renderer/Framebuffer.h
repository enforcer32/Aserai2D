#pragma once

#include <stdint.h>

namespace Aserai2D
{
	enum class FramebufferAttachmentFormat
	{
		RGBA8,
		RED_INTEGER,
	};

	struct FramebufferProperties
	{
		uint32_t Width;
		uint32_t Height;
		std::vector<FramebufferAttachmentFormat> Attachments;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferProperties& properties);
		~Framebuffer();

		void Bind();
		void Unbind();

		uint32_t GetID() const;
		uint32_t GetColorAttachmentRendererID(uint32_t index) const;
		void Resize(uint32_t width, uint32_t height);
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		int32_t ReadPixel(uint32_t attachmentIndex, uint32_t x, uint32_t y) const;
		void ClearColorAttachment(uint32_t index, int data);

	private:
		void Reset();

	private:
		uint32_t m_FrameBufferID;
		FramebufferProperties m_Properties;
		std::vector<uint32_t> m_ColorAttachments;
	};
}
