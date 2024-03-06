#pragma once

#include "A2DEnginePCH.h"
#include "A2DEngine/Asset/TextureAsset.h"

namespace Aserai2D
{
	TextureAsset::TextureAsset(const std::string& path)
	{
		m_TexturePath = path;
		m_Texture = nullptr;
		SetFlags(AssetFlag::Unloaded);
	}

	AssetType TextureAsset::GetStaticType()
	{
		return AssetType::Texture;
	}

	AssetType TextureAsset::GetType() const
	{
		return GetStaticType();
	}

	bool TextureAsset::Reload()
	{
		m_Texture = std::make_shared<Texture2D>(m_TexturePath);
		SetFlags(AssetFlag::Loaded);
		return true;
	}

	std::shared_ptr<Texture2D> TextureAsset::GetTexture()
	{
		return m_Texture;
	}

	const std::string& TextureAsset::GetTexturePath() const
	{
		return m_TexturePath;
	}
}
