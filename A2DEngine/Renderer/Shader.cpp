#include "A2DEnginePCH.h"
#include "A2DEngine/Renderer/Shader.h"
#include "A2DEngine/Core/Logger.h"
#include "A2DEngine/Utils/FileIO.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Aserai2D
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
		: m_ProgramID(0)
	{
		m_ProgramID = CreateShader(FileIO::ReadFileContent(vertexPath), FileIO::ReadFileContent(fragmentPath));
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_ProgramID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetIntArray(const std::string& name, int* values, int count)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	uint32_t Shader::CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		uint32_t program = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);
		return program;
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string& src)
	{
		uint32_t id = glCreateShader(type);
		const char* csrc = src.c_str();
		glShaderSource(id, 1, &csrc, nullptr);
		glCompileShader(id);
		PrintCompileStatus(id);
		return id;
	}

	void Shader::PrintCompileStatus(uint32_t id)
	{
		int res;
		glGetShaderiv(id, GL_COMPILE_STATUS, &res);
		if (!res)
		{
			int len;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			char* msg = (char*)alloca(len * sizeof(char));
			glGetShaderInfoLog(id, len, &len, msg);
			ASERAI_LOG_ERROR("FAILED TO COMPILE SHADER({}) {}", id, msg);
			glDeleteShader(id);
		}
	}

	int Shader::GetUniformLocation(const std::string& name) const
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int loc = glGetUniformLocation(m_ProgramID, name.c_str());
		m_UniformLocationCache[name] = loc;
		return loc;
	}
}
