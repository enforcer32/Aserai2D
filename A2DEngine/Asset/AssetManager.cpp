#include "A2DEnginePCH.h"
#include "A2DEngine/Asset/AssetManager.h"
#include "A2DEngine/Core/Logger.h"

namespace Aserai2D
{
	std::unordered_map<AssetID, std::shared_ptr<Asset>> AssetManager::s_Assets;

	bool AssetManager::OnInit()
	{
		ASERAI_LOG_DEBUG("AssetManager Initializing...");
		return true;
	}

	void AssetManager::OnShutdown()
	{
		ASERAI_LOG_DEBUG("AssetManager Shutting Down...");
	}

	AssetType AssetManager::GetAssetType(AssetID assetID)
	{
		if (HasAssetID(assetID))
			return s_Assets[assetID]->GetType();
		return AssetType::None;
	}

	bool AssetManager::HasAssetID(AssetID assetID)
	{
		if (s_Assets.find(assetID) != s_Assets.end())
			return true;
		ASERAI_LOG_DEBUG("AssetManager AssetID Not Found");
		return false;
	}

	bool AssetManager::IsAssetValid(AssetID assetID)
	{
		return HasAssetID(assetID) ? s_Assets[assetID]->IsValid() : false;
	}

	bool AssetManager::IsAssetLoaded(AssetID assetID)
	{
		return HasAssetID(assetID) ? (s_Assets[assetID]->IsValid() && s_Assets[assetID]->GetFlags() == AssetFlag::Loaded) : false;
	}

	void AssetManager::AddAsset(const std::shared_ptr<Asset>& asset)
	{
		s_Assets[asset->GetAssetID()] = asset;
	}

	void AssetManager::ReloadAsset(AssetID assetID)
	{
		if (HasAssetID(assetID))
			if (s_Assets[assetID]->Reload())
				ASERAI_LOG_DEBUG("Reloaded Asset({})", (uint64_t)assetID);
			else
				ASERAI_LOG_DEBUG("AssetManager Failed To Reload " + (uint64_t)assetID);
	}
}
