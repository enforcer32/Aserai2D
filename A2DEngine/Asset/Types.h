#pragma once

#include "A2DEngine/Core/UUID.h"

namespace Aserai2D
{
	using AssetID = UUID;

	enum class AssetType
	{
		None,
		Texture,
		Spritesheet
	};

	enum class AssetFlag
	{
		Invalid,
		Missing,
		Unloaded,
		Loaded,
	};
}
