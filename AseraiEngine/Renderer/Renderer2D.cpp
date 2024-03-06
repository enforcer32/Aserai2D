#include "AseraiEnginePCH.h"
#include "AseraiEngine/Renderer/Renderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Aserai
{
	Renderer2D::Renderer2D()
	{
		m_Initialized = false;
	}

	bool Renderer2D::Init(uint32_t batchsize)
	{
		// Mesh = Object, Material = Color or Lighting applied on object to change effects/colors
		// Texture = Material or Image Applied on Mesh or Object (Add Detail On Object)

		m_MaxQuadCount = batchsize;
		m_MaxVertexCount = m_MaxQuadCount * 4;
		m_MaxIndexCount = m_MaxQuadCount * 6;
		m_MaxTextureCount = 32;

		// CREATE SHADER
		int samplers[32];
		for (uint32_t i = 0; i < 32; i++) samplers[i] = i;
		m_QuadShader = std::make_unique<Shader>("../Assets/Shaders/QuadVertex.glsl", "../Assets/Shaders/QuadFragment.glsl");
		m_QuadShader->Bind();
		m_QuadShader->SetIntArray("u_Textures", samplers, m_MaxTextureCount);

		// CREATE VAO
		m_QuadVertexArray = std::make_unique<VertexArray>();
		m_QuadVertexArray->Bind();

		// CREATE VBO
		m_QuadVertexBuffer = std::make_shared<VertexBuffer>(m_MaxVertexCount * sizeof(QuadVertex), GL_STATIC_DRAW);

		// VBO ATTRIBUTES LAYOUT
		m_QuadVertexBuffer->SetLayout({
			{"a_Position", 3, ShaderDataType::Float},
			{"a_Color", 4, ShaderDataType::Float},
			{"a_TextureUV", 2, ShaderDataType::Float},
			{"a_TextureID", 1, ShaderDataType::Float}
			});
		m_QuadVertexArray->AddVertexBuffer(m_QuadVertexBuffer);

		// CREATE EBO
		auto indices = GenerateIndices();
		m_QuadIndexBuffer = std::make_shared<IndexBuffer>(indices.get(), m_MaxIndexCount, GL_STATIC_DRAW);
		m_QuadVertexArray->SetIndexBuffer(m_QuadIndexBuffer);

		m_QuadTemplate = CreateCenteredQuad({ 1.0f, 1.0f, 1.0f, 1.0f });
		m_QuadVertices = std::make_unique<QuadVertex[]>(m_MaxVertexCount);

		uint32_t blank = 0xffffffff;
		m_BlankTexture = std::make_shared<Texture2D>(1, 1, 4);
		m_BlankTexture->SetBuffer(&blank);

		m_Textures = std::make_unique<std::shared_ptr<Texture2D>[]>(m_MaxTextureCount);
		m_Textures[0] = m_BlankTexture;

		return m_Initialized = true;
	}

	void Renderer2D::Destroy()
	{
		m_Initialized = false;
	}

	void Renderer2D::BeginRenderer(const Camera& camera, const glm::mat4& cameraTransform)
	{
		m_QuadShader->Bind();
		m_QuadShader->SetMat4("u_ProjectionViewMatrix", (camera.GetProjection() * glm::inverse(cameraTransform)));
		m_QuadVertexIndex = 0;
		m_TextureIndex = 1;
	}

	void Renderer2D::EndRenderer()
	{
		if (m_QuadVertexIndex)
		{
			m_QuadVertexBuffer->SetBuffer(m_QuadVertices.get(), m_QuadVertexIndex * sizeof(QuadVertex));

			for (uint32_t i = 0; i < m_TextureIndex; i++)
				m_Textures[i]->Bind(i);

			m_QuadVertexArray->Bind();
			DrawIndexed(m_QuadVertexArray, ((m_QuadVertexIndex / 4) * 6));

			m_RenderStats.DrawCallCount++;
		}
	}

	void Renderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer2D::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Renderer2D::SetViewPort(int x, int y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer2D::SetDepthTesting(bool status)
	{
		status ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void Renderer2D::SetAlphaBlending(bool status)
	{
		if (status)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}

	void Renderer2D::RenderQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		auto quad = CreateQuad(position, size, color);
		for (uint32_t i = 0; i < 4; i++)
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::vec3& position, const glm::vec3& size, const std::shared_ptr<Texture2D>& texture)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		float texID = 0.0f;
		for (uint32_t i = 1; i < m_TextureIndex; i++)
		{
			if (*texture == *m_Textures[i])
			{
				texID = i;
				break;
			}
		}

		if (!texID)
		{
			if (m_TextureIndex >= m_MaxTextureCount)
				ResetBatch();

			texID = m_TextureIndex;
			m_Textures[m_TextureIndex++] = texture;
		}

		auto quad = CreateQuad(position, size, { 1.0f, 1.0f, 1.0f, 1.0f }, texID);
		for (uint32_t i = 0; i < 4; i++)
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::vec3& position, const glm::vec3& size, const std::shared_ptr<Texture2D>& texture, const std::array<glm::vec2, 4>& textureUV)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		float texID = 0.0f;
		for (uint32_t i = 1; i < m_TextureIndex; i++)
		{
			if (*texture == *m_Textures[i])
			{
				texID = i;
				break;
			}
		}

		if (!texID)
		{
			if (m_TextureIndex >= m_MaxTextureCount)
				ResetBatch();

			texID = m_TextureIndex;
			m_Textures[m_TextureIndex++] = texture;
		}

		auto quad = CreateQuad(position, size, { 1.0f, 1.0f, 1.0f, 1.0f }, texID);
		for (uint32_t i = 0; i < 4; i++)
		{
			quad[i].TextureUV = textureUV[i];
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		auto quad = m_QuadTemplate;
		for (int i = 0; i < 4; i++)
		{
			quad[i].Color = color;
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture)
	{

		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		float texID = 0.0f;
		for (uint32_t i = 1; i < m_TextureIndex; i++)
		{
			if (*texture == *m_Textures[i])
			{
				texID = i;
				break;
			}
		}

		if (!texID)
		{
			if (m_TextureIndex >= m_MaxTextureCount)
				ResetBatch();

			texID = m_TextureIndex;
			m_Textures[m_TextureIndex++] = texture;
		}

		auto quad = m_QuadTemplate;
		for (int i = 0; i < 4; i++)
		{
			quad[i].TextureID = texID;
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const std::array<glm::vec2, 4>& textureUV)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		float texID = 0.0f;
		for (uint32_t i = 1; i < m_TextureIndex; i++)
		{
			if (*texture == *m_Textures[i])
			{
				texID = i;
				break;
			}
		}

		if (!texID)
		{
			if (m_TextureIndex >= m_MaxTextureCount)
				ResetBatch();

			texID = m_TextureIndex;
			m_Textures[m_TextureIndex++] = texture;
		}

		auto quad = m_QuadTemplate;
		for (int i = 0; i < 4; i++)
		{
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			quad[i].TextureUV = textureUV[i];
			quad[i].TextureID = texID;
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];
		}

		m_RenderStats.QuadCount++;
	}

	std::array<Renderer2D::QuadVertex, 4> Renderer2D::CreateQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, float texID)
	{
		float sizemult = 1.0f;

		QuadVertex v0;
		v0.Position = position;
		v0.Color = color;
		v0.TextureUV = { 0.0f, 0.0f };
		v0.TextureID = texID;

		QuadVertex v1;
		v1.Position = { position.x + (sizemult * size.x), position.y, position.z };
		v1.Color = color;
		v1.TextureUV = { 1.0f, 0.0f };
		v1.TextureID = texID;

		QuadVertex v2;
		v2.Position = { position.x + (sizemult * size.x),  position.y + (sizemult * size.y), position.z, };
		v2.Color = color;
		v2.TextureUV = { 1.0f, 1.0f };
		v2.TextureID = texID;

		QuadVertex v3;
		v3.Position = { position.x,  position.y + (sizemult * size.y), position.z, };
		v3.Color = color;
		v3.TextureUV = { 0.0f, 1.0f };
		v3.TextureID = texID;

		return { v0, v1, v2, v3 };
	}

	std::array<Renderer2D::QuadVertex, 4> Renderer2D::CreateCenteredQuad(const glm::vec4& color, float texID)
	{
		QuadVertex v0;
		v0.Position = { -0.5f, -0.5f, 0.0f };
		v0.Color = color;
		v0.TextureUV = { 0.0f, 0.0f };
		v0.TextureID = texID;

		QuadVertex v1;
		v1.Position = { 0.5f, -0.5f, 0.0f };
		v1.Color = color;
		v1.TextureUV = { 1.0f, 0.0f };
		v1.TextureID = texID;

		QuadVertex v2;
		v2.Position = { 0.5f, 0.5f, 0.0f };
		v2.Color = color;
		v2.TextureUV = { 1.0f, 1.0f };
		v2.TextureID = texID;

		QuadVertex v3;
		v3.Position = { -0.5f, 0.5f, 0.0f };
		v3.Color = color;
		v3.TextureUV = { 0.0f, 1.0f };
		v3.TextureID = texID;

		return { v0, v1, v2, v3 };
	}

	std::shared_ptr<uint32_t[]> Renderer2D::GenerateIndices()
	{
		std::shared_ptr<uint32_t[]> indices(new uint32_t[m_MaxIndexCount]);

		uint32_t offset = 0;
		for (uint32_t i = 0; i < m_MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;
			offset += 4;
		}

		return indices;
	}

	void Renderer2D::ResetBatch()
	{
		EndRenderer();
		m_QuadVertexIndex = 0;
		m_TextureIndex = 1;
	}

	void Renderer2D::DrawIndexed(const std::unique_ptr<VertexArray>& va, unsigned int count)
	{
		va->Bind();
		glDrawElements(GL_TRIANGLES, count == 0 ? va->GetIndexBuffer()->GetSize() : count, GL_UNSIGNED_INT, nullptr);
	}
}
