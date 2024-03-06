#pragma once

#include "A2DEngine/Asset/Types.h"

namespace Aserai2D
{
	class Asset
	{
	public:
		virtual ~Asset() = default;
		static AssetType GetStaticType() { return AssetType::None; }
		virtual AssetType GetType() const { return AssetType::None; }
		virtual bool Reload() { return false; }

		AssetID GetAssetID() const { return m_ID; }
		AssetFlag GetFlags() const { return m_Flags; }
		void SetFlags(AssetFlag flags) { m_Flags = flags; }
		bool IsValid() const { return (GetType() != AssetType::None) && (GetFlags() != AssetFlag::Invalid && GetFlags() != AssetFlag::Missing); }
		bool IsLoaded() const { return GetFlags() == AssetFlag::Loaded; }

	private:
		AssetID m_ID;
		AssetFlag m_Flags;
	};
}
