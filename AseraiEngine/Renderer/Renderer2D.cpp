#include "AseraiEnginePCH.h"
#include "AseraiEngine/Renderer/Renderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Aserai
{
	uint32_t* GenerateQuadIndices(uint32_t maxIndexCount)
	{
		uint32_t* indices = new uint32_t[maxIndexCount];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < maxIndexCount; i += 6)
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

	uint32_t* GenerateLineIndices(uint32_t maxIndexCount)
	{
		uint32_t* indices = new uint32_t[maxIndexCount];
		for (uint32_t i = 0; i < maxIndexCount; i++)
			indices[i] = i;
		return indices;
	}

	std::array<QuadVertex, 4> CreateCenteredQuad(const glm::vec4& color, float texID = 0.0f)
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

	bool Renderer2D::Init(uint32_t batchsize)
	{
		// Mesh = Object, Material = Color or Lighting applied on object to change effects/colors
		// Texture = Material or Image Applied on Mesh or Object (Add Detail On Object)
		m_MaxTextureCount = 32;

		// SHADERS
		int samplers[32];
		for (uint32_t i = 0; i < 32; i++) samplers[i] = i;

		// Quad Shader
		m_QuadShader = std::make_unique<Shader>("../Assets/Shaders/QuadVertex.glsl", "../Assets/Shaders/QuadFragment.glsl");
		m_QuadShader->Bind();
		m_QuadShader->SetIntArray("u_Textures", samplers, m_MaxTextureCount);

		// Line Shader
		m_LineShader = std::make_unique<Shader>("../Assets/Shaders/LineVertex.glsl", "../Assets/Shaders/LineFragment.glsl");
		m_LineShader->Bind();

		// Texture Batch
		uint32_t blank = 0xffffffff;
		m_BlankTexture = std::make_shared<Texture2D>(1, 1, 4);
		m_BlankTexture->SetBuffer(&blank);
		m_Textures = std::make_unique<std::shared_ptr<Texture2D>[]>(m_MaxTextureCount);
		m_Textures[0] = m_BlankTexture;

		// Quad Render Batch
		RenderBatchProperties quadRenderBatchProps;
		quadRenderBatchProps.BatchSize = batchsize;
		quadRenderBatchProps.VertexCount = 4;
		quadRenderBatchProps.IndexCount = 6;
		quadRenderBatchProps.Indices = GenerateQuadIndices(batchsize * 6);
		quadRenderBatchProps.DrawType = GL_STATIC_DRAW;
		quadRenderBatchProps.Shader = m_QuadShader;
		quadRenderBatchProps.Layout = {
			{"a_Position", 3, ShaderDataType::Float},
			{"a_Color", 4, ShaderDataType::Float},
			{"a_TextureUV", 2, ShaderDataType::Float},
			{"a_TextureID", 1, ShaderDataType::Float}
		};
		m_QuadRenderBatch = std::make_unique<RenderBatch<QuadVertex>>(quadRenderBatchProps);
		m_QuadTemplate = CreateCenteredQuad({ 1.0f, 1.0f, 1.0f, 1.0f });

		// Line Render Batch
		RenderBatchProperties lineRenderBatchProps;
		lineRenderBatchProps.BatchSize = batchsize;
		lineRenderBatchProps.VertexCount = 2;
		lineRenderBatchProps.IndexCount = 2;
		lineRenderBatchProps.Indices = GenerateLineIndices(batchsize * 2);
		lineRenderBatchProps.DrawType = GL_STATIC_DRAW;
		lineRenderBatchProps.Shader = m_LineShader;
		lineRenderBatchProps.Layout = {
			{"a_Position", 3, ShaderDataType::Float},
			{"a_Color", 4, ShaderDataType::Float},
		};
		m_LineRenderBatch = std::make_unique<RenderBatch<LineVertex>>(lineRenderBatchProps);

		return m_Initialized = true;
	}

	void Renderer2D::Destroy()
	{
		m_Initialized = false;
	}

	void Renderer2D::BeginRenderer(const Camera& camera, const glm::mat4& cameraTransform)
	{
		m_ProjectionViewMatrix = (camera.GetProjection() * glm::inverse(cameraTransform));
		m_TextureIndex = 1;
		m_QuadRenderBatch->Reset();
		m_LineRenderBatch->Reset();
	}

	void Renderer2D::EndRenderer()
	{
		if (!m_QuadRenderBatch->IsEmpty())
		{
			m_QuadShader->Bind();
			m_QuadShader->SetMat4("u_ProjectionViewMatrix", m_ProjectionViewMatrix);

			for (uint32_t i = 0; i < m_TextureIndex; i++)
				m_Textures[i]->Bind(i);

			m_QuadRenderBatch->Render(GL_TRIANGLES);
			m_QuadShader->Unbind();

			m_RenderStats.DrawCallCount++;
		}

		if (!m_LineRenderBatch->IsEmpty())
		{
			m_LineShader->Bind();
			m_LineShader->SetMat4("u_ProjectionViewMatrix", m_ProjectionViewMatrix);
			m_LineRenderBatch->Render(GL_LINES);
			m_LineShader->Unbind();
		
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

	void Renderer2D::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		if(m_QuadRenderBatch->IsFull())
			ResetBatch();

		auto quad = m_QuadTemplate;
		for (int i = 0; i < 4; i++)
		{
			quad[i].Color = color;
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			m_QuadRenderBatch->Add(quad[i]);
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture)
	{
		if (m_QuadRenderBatch->IsFull())
			ResetBatch();

		float texID = GetTextureSlot(texture);
		auto quad = m_QuadTemplate;
		for (int i = 0; i < 4; i++)
		{
			quad[i].TextureID = texID;
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			m_QuadRenderBatch->Add(quad[i]);
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const std::array<glm::vec2, 4>& textureUV)
	{
		if (m_QuadRenderBatch->IsFull())
			ResetBatch();

		float texID = GetTextureSlot(texture);
		auto quad = m_QuadTemplate;
		for (int i = 0; i < 4; i++)
		{
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			quad[i].TextureUV = textureUV[i];
			quad[i].TextureID = texID;
			m_QuadRenderBatch->Add(quad[i]);
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderLine(const glm::vec3& from, const glm::vec3& to, const glm::vec4& color)
	{
		if(m_LineRenderBatch->IsFull())
			ResetBatch();

		LineVertex v0;
		v0.Position = from;
		v0.Color = color;

		LineVertex v1;
		v1.Position = to;
		v1.Color = color;

		m_LineRenderBatch->Add(v0);
		m_LineRenderBatch->Add(v1);

		m_RenderStats.LineCount++;
	}

	uint32_t Renderer2D::GetTextureSlot(const std::shared_ptr<Texture2D>& texture)
	{
		uint32_t texID = 0;
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

		return texID;
	}

	void Renderer2D::ResetBatch()
	{
		EndRenderer();
		m_TextureIndex = 1;
		m_QuadRenderBatch->Reset();
		m_LineRenderBatch->Reset();
	}
}
