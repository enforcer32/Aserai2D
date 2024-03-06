#pragma once

#include "A2DEngine/Renderer/Shader.h"
#include "A2DEngine/Renderer/Texture2D.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace Aserai2D
{
	class AssetManager
	{
	public:
		std::shared_ptr<Shader> GetShader(const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<Texture2D> GetTexture(const std::string& path);

		void Clear();

	private:
		std::unordered_map<uint32_t, std::shared_ptr<Shader>> m_Shaders;
		std::unordered_map<uint32_t, std::shared_ptr<Texture2D>> m_Textures;
	};
}
