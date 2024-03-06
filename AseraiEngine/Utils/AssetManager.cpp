#include "AseraiEnginePCH.h"
#include "AseraiEngine/Utils/AssetManager.h"

#include <fnv/fnv.h>

namespace Aserai
{
	std::shared_ptr<Shader> AssetManager::GetShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string fullpath = vertexPath + fragmentPath;
		auto hash = fnv::hash(fullpath.c_str());

		if (m_Shaders.find(hash) == m_Shaders.end())
			m_Shaders[hash] = std::make_shared<Shader>(vertexPath, fragmentPath);

		return m_Shaders[hash];
	}

	std::shared_ptr<Texture2D> AssetManager::GetTexture(const std::string& path)
	{
		auto hash = fnv::hash(path.c_str());

		if (m_Textures.find(hash) == m_Textures.end())
			m_Textures[hash] = std::make_shared<Texture2D>(path);

		return m_Textures[hash];
	}
}
