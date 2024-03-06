#pragma once

#include "A2DEngine/Asset/Asset.h"

#include <glm/glm.hpp>
#include <memory>
#include <array>
#include <vector>

namespace Aserai2D
{
	struct Sprite
	{
		uint32_t Width;
		uint32_t Height;
		AssetID Texture;
		std::array<glm::vec2, 4> TextureUV;
	};

	class SpritesheetAsset : public Asset
	{
	public:
		SpritesheetAsset(AssetID texture, uint32_t spriteWidth, uint32_t spriteHeight, uint32_t spriteCount, uint32_t spriteSpacing, const std::string& name = "Untitled");

		static AssetType GetStaticType();
		virtual AssetType GetType() const override;
		virtual bool Reload() override;

		AssetID GetTexture() const;
		uint32_t GetSpriteWidth() const;
		uint32_t GetSpriteHeight() const;
		uint32_t GetSpriteCount() const;
		uint32_t GetSpriteSpacing() const;
		const std::string& GetName() const;
		const std::vector<Sprite>& GetSprites() const;
		const Sprite& GetSprite(uint32_t index) const;

	private:
		AssetID m_Texture;
		uint32_t m_SpriteWidth;
		uint32_t m_SpriteHeight;
		uint32_t m_SpriteCount;
		uint32_t m_SpriteSpacing;
		std::string m_Name;
		std::vector<Sprite> m_Sprites;
	};
}
