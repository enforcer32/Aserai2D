#include "AseraiEnginePCH.h"
#include "AseraiEngine/Renderer/Texture2D.h"
#include "AseraiEngine/Core/Logger.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace Aserai
{
	Texture2D::Texture2D(int32_t width, int32_t height, int32_t channels)
		: m_Width(width), m_Height(height), m_Channels(channels), m_InternalFormat(GL_RGBA8), m_Format(GL_RGBA)
	{
		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_Format = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_Format = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture2D::Texture2D(const std::string& filepath, bool flipVertically)
		: m_InternalFormat(GL_RGBA8), m_Format(GL_RGBA)
	{
		stbi_set_flip_vertically_on_load(flipVertically);
		uint8_t* buffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_Format = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_Format = GL_RGB;
		}
		else
		{
			ASERAI_LOG_ERROR("TEXTURE2D WIDTH: {}, HEIGHT: {}, INVALID CHANNELS: {}", m_Width, m_Height, m_Channels);
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		if(buffer)
			stbi_image_free(buffer);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::SetBuffer(const void* data)
	{
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, data);
	}

	uint32_t Texture2D::GetID() const
	{
		return m_TextureID;
	}

	int32_t Texture2D::GetWidth() const
	{
		return m_Width;
	}
	
	int32_t Texture2D::GetHeight() const
	{
		return m_Height;
	}
	
	int32_t Texture2D::GetChannels() const
	{
		return m_Channels;
	}
}
