#include "AseraiEnginePCH.h"
#include "AseraiEngine/Scene/Scene.h"

#include "AseraiEngine/Systems/MovementSystem.h"
#include "AseraiEngine/Systems/RenderSystem.h"
#include "AseraiEngine/Systems/CameraControlSystem.h"
#include "AseraiEngine/Systems/KeyboardMovementSystem.h"
#include "AseraiEngine/Systems/CollisionSystem.h"
#include "AseraiEngine/Systems/ParticleEmitSystem.h"
#include "AseraiEngine/Systems/ParticleLifeSystem.h"

#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/CameraComponent.h"

namespace Aserai
{
	Scene::Scene(const std::string& name)
		: m_Name(name), m_Registry(nullptr)
	{
		m_Registry = std::make_shared<Registry>();

		// Register Systems
		EnableSystem<CameraControlSystem>();
		EnableSystem<CameraControlSystem>();
		EnableSystem<MovementSystem>();
		EnableSystem<RenderSystem>();
		EnableSystem<KeyboardMovementSystem>();
		EnableSystem<CollisionSystem>();
		EnableSystem<ParticleEmitSystem>();
		EnableSystem<ParticleLifeSystem>();
	}

	void Scene::OnRuntimeUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager, const std::shared_ptr<EventManager>& eventManager)
	{
		if(IsSystemEnabled<CameraControlSystem>())
			GetSystem<CameraControlSystem>()->OnUpdate(dt, inputManager);
		if (IsSystemEnabled<MovementSystem>())
			GetSystem<MovementSystem>()->OnUpdate(dt);
		if (IsSystemEnabled<KeyboardMovementSystem>())
			GetSystem<KeyboardMovementSystem>()->OnUpdate(dt, inputManager);
		if (IsSystemEnabled<CollisionSystem>())
			GetSystem<CollisionSystem>()->OnUpdate(dt, eventManager);
		if (IsSystemEnabled<ParticleEmitSystem>())
			GetSystem<ParticleEmitSystem>()->OnUpdate(dt, m_Registry, inputManager);
		if (IsSystemEnabled<ParticleLifeSystem>())
			GetSystem<ParticleLifeSystem>()->OnUpdate(dt);

		m_Registry->Sync();
	}

	void Scene::OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer, const std::shared_ptr<InputManager>& inputManager)
	{
		Entity primaryCamera = GetPrimaryCamera();
		if (primaryCamera)
		{
			renderer->BeginRenderer(primaryCamera.GetComponent<CameraComponent>().Camera, primaryCamera.GetComponent<TransformComponent>().GetTransform());
			GetSystem<RenderSystem>()->OnUpdate(dt, renderer);
			if(IsSystemEnabled<CollisionSystem>()) // && IsDebug?
				GetSystem<CollisionSystem>()->OnRender(dt, renderer, inputManager);
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
		entity.SetTag(name);
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
