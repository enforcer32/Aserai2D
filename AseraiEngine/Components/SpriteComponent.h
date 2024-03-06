#pragma once

#include "AseraiEngine/Renderer/Texture2D.h"

#include <glm/glm.hpp>
#include <memory>

namespace Aserai
{
	struct SpriteComponent
	{
		std::shared_ptr<Texture2D> Texture;
		glm::vec4 Color;
		uint32_t Width;
		uint32_t Height;
		uint32_t ZIndex;
		float TextureX;
		float TextureY;
		uint32_t TextureW;
		uint32_t TextureH;
		bool Fixed;

		SpriteComponent(const glm::vec4& color = glm::vec4({ 1.0f, 0.0f, 0.0f, 1.0f }), uint32_t width = 1, uint32_t height = 1, uint32_t zIndex = 0, bool fixed = false)
			: Texture(nullptr), Color(color), Width(width), Height(height), ZIndex(zIndex), TextureX(0), TextureY(0), TextureW(0), TextureH(0), Fixed(fixed)
		{
		}

		SpriteComponent(const std::shared_ptr<Texture2D>& texture, uint32_t width = 1, uint32_t height = 1, uint32_t zIndex = 0, float textureX = 0, float textureY = 0, uint32_t textureW = 0, uint32_t textureH = 0, bool fixed = false)
			: Texture(texture), Color({1.0f, 0.0f, 0.0f, 1.0f}), Width(width), Height(height), ZIndex(zIndex), TextureX(textureX), TextureY(textureY), TextureW(textureW), TextureH(textureH), Fixed(fixed)
		{
		}
	};
}
