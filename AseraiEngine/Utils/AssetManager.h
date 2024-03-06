#pragma once

#include "AseraiEngine/Renderer/Shader.h"
#include "AseraiEngine/Renderer/Texture2D.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace Aserai
{
	class AssetManager
	{
	public:
		std::shared_ptr<Shader> GetShader(const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<Texture2D> GetTexture(const std::string& path);

	private:
		std::unordered_map<uint32_t, std::shared_ptr<Shader>> m_Shaders;
		std::unordered_map<uint32_t, std::shared_ptr<Texture2D>> m_Textures;
	};
}
