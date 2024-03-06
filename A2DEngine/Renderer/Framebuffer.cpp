#include "A2DEnginePCH.h"
#include "A2DEngine/Renderer/Framebuffer.h"
#include "A2DEngine/Core/Assertion.h"

#include <glad/glad.h>

namespace Aserai2D
{
	Framebuffer::Framebuffer(const FramebufferProperties& properties)
		: m_FrameBufferID(0), m_Properties(properties)
	{
		Reset();
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_FrameBufferID);
		for (uint32_t i = 0; i < m_ColorAttachments.size(); i++)
			glDeleteTextures(1, &m_ColorAttachments[i]);
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glViewport(0, 0, m_Properties.Width, m_Properties.Height);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t Framebuffer::GetID() const
	{ 
		return m_FrameBufferID;
	}
	
	uint32_t Framebuffer::GetColorAttachmentRendererID(uint32_t index) const
	{ 
		return m_ColorAttachments[index];
	}
	
	void Framebuffer::Resize(uint32_t width, uint32_t height)
	{ 
		m_Properties.Width = width;
		m_Properties.Height = height;
		Reset();
	}
	
	uint32_t Framebuffer::GetWidth() const
	{ 
		return m_Properties.Width;
	}
	
	uint32_t Framebuffer::GetHeight() const
	{ 
		return m_Properties.Height; 
	}

	int32_t Framebuffer::ReadPixel(uint32_t attachmentIndex, uint32_t x, uint32_t y) const
	{
		int data;
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		glReadPixels(x, y, m_Properties.Width, m_Properties.Height, GL_RED_INTEGER, GL_INT, &data);
		return data;
	}

	void Framebuffer::Reset()
	{
		if (m_FrameBufferID)
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			for(uint32_t i = 0; i < m_ColorAttachments.size(); i++)
				glDeleteTextures(1, &m_ColorAttachments[i]);
		}

		glCreateFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

		for (uint32_t i = 0; i < m_Properties.Attachments.size(); i++)
		{
			uint32_t textureID;
			glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			switch (m_Properties.Attachments[i])
			{
			case FramebufferAttachmentFormat::RGBA:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Properties.Width, m_Properties.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				break;
			case FramebufferAttachmentFormat::RED_INTEGER:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_Properties.Width, m_Properties.Height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);
				break;
			default:
				break;
			}

			glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, i);
			m_ColorAttachments.push_back(textureID);
		}

		ASERAI_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "glCheckFrameBufferStatus(FrameBuffer FAILED)");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
