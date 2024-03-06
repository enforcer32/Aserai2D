#include "A2DEnginePCH.h"
#include "A2DEngine/Renderer/VertexBufferLayout.h"

#include <glad/glad.h>

namespace Aserai2D
{
	uint32_t GetSizeofShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return sizeof(GLboolean);
		case ShaderDataType::Int:
			return sizeof(GLint);
		case ShaderDataType::UInt:
			return sizeof(GLuint);
		case ShaderDataType::Float:
			return sizeof(GLfloat);
		case ShaderDataType::Double:
			return sizeof(GLdouble);
		default:
			break;
		}

		return 0;
	}

	uint32_t ConvertShaderDataTypeToGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return GL_BOOL;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::UInt:
			return GL_UNSIGNED_INT;
		case ShaderDataType::Float:
			return GL_FLOAT;
		case ShaderDataType::Double:
			return GL_DOUBLE;
		default:
			break;
		}

		return 0;
	}

	VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferAttrib>& attribs)
		: m_Attributes(attribs), m_Stride(0)
	{
		CalculateOffsets();
	}

	const std::vector<VertexBufferAttrib>& VertexBufferLayout::GetAttributes() const
	{
		return m_Attributes;
	}

	uint32_t VertexBufferLayout::GetStride() const
	{
		return m_Stride;
	}

	void VertexBufferLayout::CalculateOffsets()
	{
		uint32_t offset = 0;
		for (auto& attrib : m_Attributes)
		{
			attrib.Offset = offset;
			offset += attrib.Size * GetSizeofShaderDataType(attrib.Type);
			m_Stride += attrib.Size * GetSizeofShaderDataType(attrib.Type);
		}
	}
}
