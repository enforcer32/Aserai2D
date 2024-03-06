#pragma once

#include "A2DEngine/Renderer/Shader.h"
#include "A2DEngine/Renderer/VertexArray.h"
#include "A2DEngine/Renderer/VertexBuffer.h"
#include "A2DEngine/Renderer/IndexBuffer.h"
#include "A2DEngine/Renderer/Render.h"

namespace Aserai2D
{
	struct RenderBatchProperties
	{
		uint32_t BatchSize;
		uint32_t VertexCount;
		uint32_t IndexCount;
		uint32_t* Indices;
		uint32_t DrawType;
		std::shared_ptr<Shader> Shader;
		VertexBufferLayout Layout;
	};

	template<typename Vertex>
	class RenderBatch
	{
	public:
		RenderBatch(const RenderBatchProperties& properties)
			: m_Properties(properties)
		{
			m_MaxVertexCount = m_Properties.BatchSize * m_Properties.VertexCount;
			m_MaxIndexCount = m_Properties.BatchSize * m_Properties.IndexCount;
			m_Indices = m_Properties.Indices;

			m_VertexArray = std::make_unique<VertexArray>();
			m_VertexArray->Bind();

			m_VertexBuffer = std::make_shared<VertexBuffer>(m_MaxVertexCount * sizeof(Vertex), m_Properties.DrawType);
			m_VertexBuffer->SetLayout(m_Properties.Layout);
			m_VertexArray->AddVertexBuffer(m_VertexBuffer);

			m_IndexBuffer = std::make_shared<IndexBuffer>(m_Properties.Indices, m_MaxIndexCount, m_Properties.DrawType);
			m_VertexArray->SetIndexBuffer(m_IndexBuffer);
			m_VertexArray->Unbind();

			m_Vertices = new Vertex[m_MaxVertexCount];
		}

		~RenderBatch()
		{
			delete[] m_Vertices;
			delete[] m_Indices;
		}

		void Reset()
		{
			m_VertexIndex = 0;
		}

		bool IsFull() const
		{
			return m_VertexIndex >= m_MaxVertexCount;
		}

		bool IsEmpty() const
		{
			return m_VertexIndex == 0;
		}

		void Add(const Vertex& vertex)
		{
			m_Vertices[m_VertexIndex++] = vertex;
		}

		void Render(uint32_t drawMode)
		{
			m_VertexBuffer->SetBuffer(m_Vertices, m_VertexIndex * sizeof(Vertex));
			m_VertexArray->Bind();
			Render::DrawIndexed(drawMode, *m_VertexArray, ((m_VertexIndex / m_Properties.VertexCount) * m_Properties.IndexCount));
		}

	private:
		RenderBatchProperties m_Properties;
		uint32_t m_MaxVertexCount;
		uint32_t m_MaxIndexCount;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		Vertex* m_Vertices;
		uint32_t m_VertexIndex;
		uint32_t* m_Indices;
	};
}
