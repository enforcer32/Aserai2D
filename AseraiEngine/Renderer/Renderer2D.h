#pragma once

#include "AseraiEngine/Renderer/Shader.h"
#include "AseraiEngine/Renderer/VertexArray.h"
#include "AseraiEngine/Renderer/VertexBuffer.h"
#include "AseraiEngine/Renderer/IndexBuffer.h"
#include "AseraiEngine/Renderer/Texture2D.h"

#include <memory>
#include <array>
#include <glm/glm.hpp>

namespace Aserai
{
	struct RenderStats
	{
		uint32_t DrawCallCount = 0;
		uint32_t QuadCount = 0;
		uint32_t GetVertexCount() const { return QuadCount * 4; }
		uint32_t GetIndexCount() const { return QuadCount * 6; }
	};

	class Renderer2D
	{
	public:
		Renderer2D();

		bool Init(uint32_t batchsize);
		void Destroy();

		void BeginRenderer();
		void EndRenderer();

		void Clear();
		void SetClearColor(const glm::vec4& color);
		void SetViewPort(int x, int y, uint32_t width, uint32_t height);
		void SetDepthTesting(bool status);
		void SetAlphaBlending(bool status);

		void RenderQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
		void RenderQuad(const glm::vec3& position, const glm::vec3& size, const std::shared_ptr<Texture2D>& texture);

		void RenderQuad(const glm::mat4& transform, const glm::vec4& color);
		void RenderQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture);

		inline const RenderStats& GetRenderStats() const { return m_RenderStats; }
		inline void ResetRenderStats() { memset(&m_RenderStats, 0, sizeof(RenderStats)); }

	private:
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TextureUV;
			float TextureID;
		};

		std::array<QuadVertex, 4> CreateQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, float texID = 0.0f);
		std::array<QuadVertex, 4> CreateCenteredQuad(const glm::vec4& color, float texID = 0.0f);
		std::shared_ptr<uint32_t[]> GenerateIndices();
		void ResetBatch();
		void DrawIndexed(const std::unique_ptr<VertexArray>& va, unsigned int count = 0);


	private:
		bool m_Initialized;

		uint32_t m_MaxQuadCount;
		uint32_t m_MaxVertexCount;
		uint32_t m_MaxIndexCount;
		uint32_t m_MaxTextureCount;

		std::unique_ptr<Shader> m_QuadShader;
		std::unique_ptr<VertexArray> m_QuadVertexArray;
		std::shared_ptr<VertexBuffer> m_QuadVertexBuffer;
		std::shared_ptr<IndexBuffer> m_QuadIndexBuffer;

		std::array<QuadVertex, 4> m_QuadTemplate;
		std::unique_ptr<QuadVertex[]> m_QuadVertices; 
		uint32_t m_QuadVertexIndex;

		std::shared_ptr<Texture2D> m_BlankTexture;
		std::unique_ptr<std::shared_ptr<Texture2D>[]> m_Textures;
		uint32_t m_TextureIndex;

		RenderStats m_RenderStats;
	};
}
