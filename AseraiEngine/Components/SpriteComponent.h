#pragma once

#include "AseraiEngine/Renderer/Texture2D.h"

#include <glm/glm.hpp>
#include <memory>

namespace Aserai
{
	struct SpriteComponent
	{
		glm::vec4 Color;
		std::shared_ptr<Texture2D> Texture;
		uint32_t Width;
		uint32_t Height;
		uint32_t ZIndex;
		bool Fixed;

		SpriteComponent(const glm::vec4& color = glm::vec4({ 1.0f, 0.0f, 0.0f, 1.0f }), uint32_t width = 0, uint32_t height = 0, uint32_t zIndex = 0, bool fixed = false)
			: Color(color), Width(width), Height(height), ZIndex(zIndex), Fixed(fixed), Texture(nullptr)
		{
		}

		SpriteComponent(const std::shared_ptr<Texture2D>& texture, uint32_t width = 0, uint32_t height = 0, uint32_t zIndex = 0, bool fixed = false)
			: Texture(texture), Width(width), Height(height), ZIndex(zIndex), Fixed(fixed), Color({ 1.0f, 0.0f, 0.0f, 1.0f })
		{
		}
	};
}
