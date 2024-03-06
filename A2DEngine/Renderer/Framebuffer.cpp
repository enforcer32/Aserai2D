#include "A2DEnginePCH.h"
#include "A2DEngine/Renderer/Framebuffer.h"
#include "A2DEngine/Core/Assertion.h"

#include <glad/glad.h>

namespace Aserai2D
{
	Framebuffer::Framebuffer(uint32_t width, uint32_t height)
		: m_FrameBufferID(0), m_Width(width), m_Height(height)
	{
		Reset();
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_FrameBufferID);
		glDeleteTextures(1, &m_ColorTextureID);
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t Framebuffer::GetID() const
	{ 
		return m_FrameBufferID;
	}
	
	uint32_t Framebuffer::GetColorTextureID() const
	{ 
		return m_ColorTextureID;
	}
	
	void Framebuffer::Resize(uint32_t width, uint32_t height)
	{ 
		m_Width = width; m_Height = height; Reset(); 
	}
	
	uint32_t Framebuffer::GetWidth() const
	{ 
		return m_Width;
	}
	
	uint32_t Framebuffer::GetHeight() const
	{ 
		return m_Height; 
	}

	void Framebuffer::Reset()
	{
		if (m_FrameBufferID)
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			glDeleteTextures(1, &m_ColorTextureID);
		}

		glCreateFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorTextureID);
		glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTextureParameteri(m_ColorTextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_ColorTextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureID, 0);

		ASERAI_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "glCheckFrameBufferStatus(FrameBuffer FAILED)");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
