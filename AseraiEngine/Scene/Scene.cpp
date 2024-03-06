#include "AseraiEnginePCH.h"
#include "AseraiEngine/Scene/Scene.h"

#include "AseraiEngine/Systems/MovementSystem.h"
#include "AseraiEngine/Systems/RenderSystem.h"
#include "AseraiEngine/Systems/CameraControlSystem.h"
#include "AseraiEngine/Systems/KeyboardMovementSystem.h"
#include "AseraiEngine/Systems/CollisionSystem.h"

#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/CameraComponent.h"

namespace Aserai
{
	Scene::Scene(const std::string& name)
		: m_Name(name), m_Registry(nullptr)
	{
		m_Registry = std::make_shared<Registry>();

		// Register Systems
		m_Registry->AddSystem<CameraControlSystem>();
		m_Registry->AddSystem<MovementSystem>();
		m_Registry->AddSystem<RenderSystem>();
		m_Registry->AddSystem<KeyboardMovementSystem>();
		m_Registry->AddSystem<CollisionSystem>();
	}

	void Scene::OnRuntimeUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager, const std::shared_ptr<EventManager>& eventManager)
	{
		if(m_Registry->HasSystem<CameraControlSystem>())
			m_Registry->GetSystem<CameraControlSystem>().OnUpdate(dt, inputManager);
		if (m_Registry->HasSystem<MovementSystem>())
			m_Registry->GetSystem<MovementSystem>().OnUpdate(dt);
		if (m_Registry->HasSystem<KeyboardMovementSystem>())
			m_Registry->GetSystem<KeyboardMovementSystem>().OnUpdate(dt, inputManager);
		if (m_Registry->HasSystem<CollisionSystem>())
			m_Registry->GetSystem<CollisionSystem>().OnUpdate(dt, eventManager);

		m_Registry->Sync();
	}

	void Scene::OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer, const std::shared_ptr<InputManager>& inputManager)
	{
		Entity primaryCamera = GetPrimaryCamera();
		if (primaryCamera)
		{
			renderer->BeginRenderer(primaryCamera.GetComponent<CameraComponent>().Camera, primaryCamera.GetComponent<TransformComponent>().GetTransform());
			m_Registry->GetSystem<RenderSystem>().OnUpdate(dt, renderer); // DON'T CHECK FOR HasComponent
			m_Registry->GetSystem<CollisionSystem>().OnRender(dt, renderer, inputManager);
			renderer->EndRenderer();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		auto& cameras = m_Registry->GetEntitiesWithComponent<CameraComponent>();
		for (auto entity : cameras)
		{
			auto component = entity.GetComponent<CameraComponent>();
			if (!component.Fixed)
				component.Camera.SetViewport(width, height);
		}
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

	Entity Scene::GetPrimaryCamera()
	{
		auto& cameras = m_Registry->GetEntitiesWithComponent<CameraComponent>();
		for (auto entity : cameras)
		{
			auto component = entity.GetComponent<CameraComponent>();
			if (component.Primary)
				return entity;
		}
		return {};
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
