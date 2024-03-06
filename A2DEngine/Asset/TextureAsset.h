#pragma once

#include "A2DEngine/Asset/Asset.h"
#include "A2DEngine/Renderer/Texture2D.h"

#include <memory>

namespace Aserai2D
{
	class TextureAsset : public Asset
	{
	public:
		TextureAsset(const std::string& path);
		static AssetType GetStaticType();
		virtual AssetType GetType() const override;
		virtual bool Reload() override;
		std::shared_ptr<Texture2D> GetTexture();
		const std::string& GetTexturePath() const;

	private:
		std::string m_TexturePath;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
