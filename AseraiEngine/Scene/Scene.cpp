#include "AseraiEnginePCH.h"
#include "AseraiEngine/Scene/Scene.h"

#include "AseraiEngine/Systems/MovementSystem.h"
#include "AseraiEngine/Systems/RenderSystem.h"

#include "AseraiEngine/Components/TransformComponent.h"

namespace Aserai
{
	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
		m_Registry = std::make_shared<Registry>();

		// Register Systems
		m_Registry->AddSystem<MovementSystem>();
		m_Registry->AddSystem<RenderSystem>();
	}

	void Scene::OnRuntimeUpdate(DeltaTime dt)
	{
		m_Registry->GetSystem<MovementSystem>().Update(dt);

		m_Registry->Sync();
	}

	void Scene::OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer)
	{
		renderer->BeginRenderer();
		m_Registry->GetSystem<RenderSystem>().Update(dt, renderer);
		renderer->EndRenderer();
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = m_Registry->CreateEntity();
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry->DestroyEntity(entity);
	}

	void Scene::SetName(const std::string& name)
	{
		m_Name = name;
	}

	const std::string& Scene::GetName() const
	{
		return m_Name;
	}
}
