#pragma once

#include "A2DEngine/Asset/Asset.h"
#include "A2DEngine/Renderer/Shader.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace Aserai2D
{
	class AssetManager
	{
	public:
		static bool OnInit();
		static void OnShutdown();
		static AssetType GetAssetType(AssetID assetID);
		static bool HasAssetID(AssetID assetID);
		static bool IsAssetValid(AssetID assetID);
		static bool IsAssetLoaded(AssetID assetID);
		static void AddAsset(const std::shared_ptr<Asset>& asset);
		static void ReloadAsset(AssetID assetID);
		static const std::unordered_map<AssetID, std::shared_ptr<Asset>>& GetAssets();

		template<typename T, typename ...Args>
		static AssetID CreateAsset(Args&& ...args)
		{
			std::shared_ptr<T> asset = std::make_shared<T>(std::forward<Args>(args)...);
			std::shared_ptr<Asset> base = std::static_pointer_cast<Asset>(asset);
			s_Assets[base->GetAssetID()] = asset;
			ASERAI_LOG_DEBUG("Created Asset({})", base->GetAssetID());
			ReloadAsset(base->GetAssetID());
			return base->GetAssetID();
		}

		template<typename T>
		static std::shared_ptr<T> GetAsset(AssetID assetID)
		{
			if (HasAssetID(assetID))
				return std::dynamic_pointer_cast<T>(s_Assets[assetID]);
			return false;
		}

		template<typename T>
		static std::vector<std::shared_ptr<T>> GetAssets()
		{
			std::vector<std::shared_ptr<T>> assets;
			for (auto& asset : s_Assets)
				if (asset.second->GetType() == T::GetStaticType())
					assets.push_back(std::static_pointer_cast<T>(asset.second));
			return assets;
		}

	private:
		static std::unordered_map<AssetID, std::shared_ptr<Asset>> s_Assets;
	};
}
