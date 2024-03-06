#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/RenderSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"


namespace Aserai
{
	RenderSystem::RenderSystem()
	{
		RegisterComponent<TransformComponent>();
	}

	void RenderSystem::Update(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer)
	{
		for (auto& entity : GetEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			renderer->RenderQuad(transform.GetTransform(), { 1.0f, 1.0f, 0.0, 1.0f });
		}
	}
}
