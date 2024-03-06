#pragma once

#include <string>
#include <vector>

namespace Aserai2D
{
	enum class ShaderDataType
	{
		Unknown, Bool, Int, UInt, Float, Double
	};

	uint32_t GetSizeofShaderDataType(ShaderDataType type);
	uint32_t ConvertShaderDataTypeToGLType(ShaderDataType type);

	struct VertexBufferAttrib
	{
		std::string Name;
		uint32_t Size;
		ShaderDataType Type;
		bool Normalized;
		uint32_t Offset;

		VertexBufferAttrib(const std::string& name, uint32_t size, ShaderDataType type, bool normalized = false)
			: Name(name), Size(size), Type(type), Normalized(normalized), Offset(0)
		{
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() = default;
		VertexBufferLayout(const std::initializer_list<VertexBufferAttrib>& attribs);

		const std::vector<VertexBufferAttrib>& GetAttributes() const;
		uint32_t GetStride() const;

	private:
		void CalculateOffsets();

	private:
		std::vector<VertexBufferAttrib> m_Attributes;
		uint32_t m_Stride;
	};
}
