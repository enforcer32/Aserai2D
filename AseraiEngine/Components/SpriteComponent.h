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
		float SrcX;
		float SrcY;
		uint32_t ZIndex;
		bool Fixed;

		SpriteComponent(const glm::vec4& color = glm::vec4({ 1.0f, 0.0f, 0.0f, 1.0f }), uint32_t width = 0, uint32_t height = 0, float srcX = 0, float srcY = 0, uint32_t zIndex = 0, bool fixed = false)
			: Texture(nullptr), Color(color), Width(width), Height(height), SrcX(srcX), SrcY(srcY), ZIndex(zIndex), Fixed(fixed)
		{
		}

		SpriteComponent(const std::shared_ptr<Texture2D>& texture, uint32_t width = 0, uint32_t height = 0, float srcX = 0, float srcY = 0, uint32_t zIndex = 0, bool fixed = false)
			: Texture(texture), Color({1.0f, 0.0f, 0.0f, 1.0f}), Width(width), Height(height), SrcX(srcX), SrcY(srcY), ZIndex(zIndex), Fixed(fixed)
		{
		}
	};
}
