#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Aserai2D
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetIntArray(const std::string& name, int* values, int count);
		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		uint32_t CompileShader(uint32_t type, const std::string& src);
		void PrintCompileStatus(uint32_t id);
		int GetUniformLocation(const std::string& name) const;

	private:
		uint32_t m_ProgramID;
		mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}
