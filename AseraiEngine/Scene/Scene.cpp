#include "AseraiEnginePCH.h"
#include "AseraiEngine/Scene/Scene.h"

#include "AseraiEngine/Systems/MovementSystem.h"
#include "AseraiEngine/Systems/RenderSystem.h"
#include "AseraiEngine/Systems/CameraControlSystem.h"

#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/CameraComponent.h"

namespace Aserai
{
	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
		m_Registry = std::make_shared<Registry>();

		// Register Systems
		m_Registry->AddSystem<CameraControlSystem>();
		m_Registry->AddSystem<MovementSystem>();
		m_Registry->AddSystem<RenderSystem>();
	}

	void Scene::OnRuntimeUpdate(DeltaTime dt, const std::shared_ptr<InputManager>& inputManager)
	{
		m_Registry->GetSystem<CameraControlSystem>().OnUpdate(dt, inputManager);
		m_Registry->GetSystem<MovementSystem>().OnUpdate(dt);

		m_Registry->Sync();
	}

	void Scene::OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer)
	{
		Entity primaryCamera = GetPrimaryCamera();
		if (primaryCamera)
		{
			renderer->BeginRenderer(primaryCamera.GetComponent<CameraComponent>().Camera, primaryCamera.GetComponent<TransformComponent>().GetTransform());
			m_Registry->GetSystem<RenderSystem>().OnUpdate(dt, renderer);
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
