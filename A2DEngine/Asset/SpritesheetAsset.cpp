#include "A2DEnginePCH.h"
#include "A2DEngine/Asset/SpritesheetAsset.h"
#include "A2DEngine/Asset/AssetManager.h"
#include "A2DEngine/Asset/TextureAsset.h"

namespace Aserai2D
{
	SpritesheetAsset::SpritesheetAsset(AssetID texture, uint32_t spriteWidth, uint32_t spriteHeight, uint32_t spriteCount, uint32_t spriteSpacing, const std::string& name)
		: m_Texture(texture), m_SpriteWidth(spriteWidth), m_SpriteHeight(spriteHeight), m_SpriteCount(spriteCount), m_SpriteSpacing(spriteSpacing), m_Name(name)
	{
		SetFlags(AssetFlag::Unloaded);
	}

	AssetType SpritesheetAsset::GetStaticType()
	{
		return AssetType::Spritesheet;
	}

	AssetType SpritesheetAsset::GetType() const
	{
		return GetStaticType();
	}

	bool SpritesheetAsset::Reload()
	{
		uint32_t textureX = 0, textureY = 0;
		auto& texture = AssetManager::GetAsset<TextureAsset>(m_Texture)->GetTexture();

		for (uint32_t i = 0; i < m_SpriteCount; i++)
		{
			std::array<glm::vec2, 4> textureUV;
			textureUV[0] = { ((float)(textureX * m_SpriteWidth) / texture->GetWidth()), ((float)(textureY * m_SpriteHeight) / texture->GetHeight()) }; // BOTTOM LEFT
			textureUV[1] = { ((float)((textureX + 1) * m_SpriteWidth) / texture->GetWidth()), ((float)(textureY * m_SpriteHeight) / texture->GetHeight()) }; // BOTTOM RIGHT
			textureUV[2] = { ((float)((textureX + 1) * m_SpriteWidth) / texture->GetWidth()), ((float)((textureY + 1) * m_SpriteHeight) / texture->GetHeight()) }; // TOP RIGHT
			textureUV[3] = { ((float)(textureX * m_SpriteWidth) / texture->GetWidth()), ((float)((textureY + 1) * m_SpriteHeight) / texture->GetHeight()) }; // TOP LEFT

			Sprite sprite;
			sprite.Width = m_SpriteWidth;
			sprite.Height = m_SpriteHeight;
			sprite.Texture = m_Texture;
			sprite.TextureUV = textureUV;

			textureX++;
			if (textureX >= (texture->GetWidth() / m_SpriteWidth))
			{
				textureX = 0;
				textureY++;
			}

			m_Sprites.emplace_back(sprite);
		}

		SetFlags(AssetFlag::Loaded);
		return true;
	}

	AssetID SpritesheetAsset::GetTexture() const
	{
		return m_Texture;
	}

	uint32_t SpritesheetAsset::GetSpriteWidth() const
	{
		return m_SpriteWidth;
	}

	uint32_t SpritesheetAsset::GetSpriteHeight() const
	{
		return m_SpriteHeight;
	}

	uint32_t SpritesheetAsset::GetSpriteCount() const
	{
		return m_SpriteCount;
	}

	uint32_t SpritesheetAsset::GetSpriteSpacing() const
	{
		return m_SpriteSpacing;
	}

	const std::string& SpritesheetAsset::GetName() const
	{
		return m_Name;
	}

	const std::vector<Sprite>& SpritesheetAsset::GetSprites() const
	{
		return m_Sprites;
	}

	const Sprite& SpritesheetAsset::GetSprite(uint32_t index) const
	{
		return m_Sprites[index];
	}
}
