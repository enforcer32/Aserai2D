#pragma once

#include "AseraiEngine/Renderer/Shader.h"
#include "AseraiEngine/Renderer/VertexArray.h"
#include "AseraiEngine/Renderer/VertexBuffer.h"
#include "AseraiEngine/Renderer/IndexBuffer.h"
#include "AseraiEngine/Renderer/Texture2D.h"
#include "AseraiEngine/Renderer/Camera.h"
#include "AseraiEngine/Renderer/RenderBatch.h"

#include <memory>
#include <array>
#include <glm/glm.hpp>

namespace Aserai
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureUV;
		float TextureID;
	};

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
		bool Init(uint32_t batchsize);
		void Destroy();

		void BeginRenderer(const Camera& camera, const glm::mat4& cameraTransform);
		void EndRenderer();

		void Clear();
		void SetClearColor(const glm::vec4& color);
		void SetViewPort(int x, int y, uint32_t width, uint32_t height);
		void SetDepthTesting(bool status);
		void SetAlphaBlending(bool status);

		void RenderQuad(const glm::mat4& transform, const glm::vec4& color);
		void RenderQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture);
		void RenderQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const std::array<glm::vec2, 4>& textureUV);

		inline const RenderStats& GetRenderStats() const { return m_RenderStats; }
		inline void ResetRenderStats() { memset(&m_RenderStats, 0, sizeof(RenderStats)); }

	private:
		uint32_t GetTextureSlot(const std::shared_ptr<Texture2D>& texture);
		void ResetBatch();

	private:
		bool m_Initialized = false;

		// TEXTURE
		uint32_t m_MaxTextureCount;
		std::shared_ptr<Texture2D> m_BlankTexture;
		std::unique_ptr<std::shared_ptr<Texture2D>[]> m_Textures;
		uint32_t m_TextureIndex;

		// QUAD
		std::shared_ptr<Shader> m_QuadShader;
		std::array<QuadVertex, 4> m_QuadTemplate;
		std::unique_ptr<RenderBatch<QuadVertex>> m_QuadRenderBatch;

		RenderStats m_RenderStats;
	};
}
