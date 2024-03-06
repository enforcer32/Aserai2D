#pragma once

#include <string>

namespace Aserai2D
{
	class Texture2D
	{
	public:
		Texture2D(int32_t width, int32_t height, int32_t channels);
		Texture2D(const std::string& filepath, bool flipVertically = true);
		~Texture2D();

		void Bind(uint32_t slot = 0) const;
		void Unbind() const;
		void SetBuffer(const void* data);

		uint32_t GetID() const;
		int32_t GetWidth() const;
		int32_t GetHeight() const;
		int32_t GetChannels() const;

		inline bool operator==(const Texture2D& rhs) const { return m_TextureID == rhs.GetID(); }
		inline bool operator!=(const Texture2D& rhs) const { return m_TextureID != rhs.GetID(); }

	private:
		uint32_t m_TextureID;
		int32_t m_Width, m_Height, m_Channels;
		uint32_t m_InternalFormat, m_Format;
	};
}
