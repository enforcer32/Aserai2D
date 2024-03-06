#include "A2DEnginePCH.h"
#include "A2DEngine/Scene/Scene.h"

#include "A2DEngine/Systems/MovementSystem.h"
#include "A2DEngine/Systems/RenderSystem.h"
#include "A2DEngine/Systems/CameraControlSystem.h"
#include "A2DEngine/Systems/KeyboardMovementSystem.h"

#include "A2DEngine/Components/TransformComponent.h"
#include "A2DEngine/Components/CameraComponent.h"

namespace Aserai2D
{
	Scene::Scene(const std::string& name)
		: m_Name(name), m_Registry(nullptr)
	{
		m_Registry = std::make_shared<Registry>();

		// Register Systems
		EnableSystem<CameraControlSystem>();
		EnableSystem<MovementSystem>();
		EnableSystem<RenderSystem>();
		EnableSystem<KeyboardMovementSystem>();
	}

	void Scene::OnRuntimeUpdate(DeltaTime dt, const std::shared_ptr<EventManager>& eventManager)
	{
		if(IsSystemEnabled<CameraControlSystem>())
			GetSystem<CameraControlSystem>()->OnUpdate(dt);
		if (IsSystemEnabled<MovementSystem>())
			GetSystem<MovementSystem>()->OnUpdate(dt);
		if (IsSystemEnabled<KeyboardMovementSystem>())
			GetSystem<KeyboardMovementSystem>()->OnUpdate(dt);

		m_Registry->Sync();
	}

	void Scene::OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer)
	{
		Entity primaryCamera = GetPrimaryCamera();
		if (primaryCamera)
		{
			renderer->BeginRenderer(primaryCamera.GetComponent<CameraComponent>().Camera, primaryCamera.GetComponent<TransformComponent>().GetTransform());
			GetSystem<RenderSystem>()->OnUpdate(dt, renderer);
			renderer->EndRenderer();
		}
	}

	void Scene::OnEditorUpdate(DeltaTime dt, const std::shared_ptr<EventManager>& eventManager)
	{
		if (IsSystemEnabled<CameraControlSystem>())
			GetSystem<CameraControlSystem>()->OnUpdate(dt);
		if (IsSystemEnabled<MovementSystem>())
			GetSystem<MovementSystem>()->OnUpdate(dt);
		if (IsSystemEnabled<KeyboardMovementSystem>())
			GetSystem<KeyboardMovementSystem>()->OnUpdate(dt);

		m_Registry->Sync();
	}

	void Scene::OnEditorRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer, const std::shared_ptr<EditorCamera>& editorCamera)
	{
		renderer->BeginRenderer(*editorCamera, editorCamera->GetTransformMatrix());		
		RenderGridLines(renderer);
		GetSystem<RenderSystem>()->OnUpdate(dt, renderer);
		renderer->EndRenderer();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_Viewport = { width, height };
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
		entity.SetUUID(UUID());
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

	void Scene::SetViewportFocus(bool state)
	{
		m_ViewportFocused = state;
	}

	std::shared_ptr<Registry> Scene::GetRegistry()
	{
		return m_Registry;
	}

	const glm::vec2& Scene::GetViewport() const
	{
		return m_Viewport;
	}

	void Scene::SetViewport(uint32_t width, uint32_t height)
	{
		m_Viewport = { width, height };
	}

	const glm::vec2& Scene::GetViewportPosition() const
	{
		return m_ViewportPosition;
	}

	void Scene::SetViewportPosition(const glm::vec2& position)
	{
		m_ViewportPosition = position;
	}

	std::shared_ptr<EditorCamera> Scene::GetEditorCamera()
	{
		return m_EditorCamera;
	}

	void Scene::SetEditorCamera(const std::shared_ptr<EditorCamera>& editorCamera)
	{
		m_EditorCamera = editorCamera;
	}

	void Scene::SetGridLinesState(bool state)
	{
		m_RenderGridLines = state;
	}

	void Scene::RenderGridLines(const std::shared_ptr<Renderer2D>& renderer, const glm::vec4& color)
	{
		if (m_RenderGridLines)
		{
			float orthoSize = m_EditorCamera->GetOrthographicSize() + 2.5;
			const auto& cameraPos = m_EditorCamera->GetTranslation();

			for (int i = -orthoSize; i <= orthoSize; i++)
			{
				renderer->RenderLine({ -orthoSize + (int)cameraPos.x, i + (int)cameraPos.y - 0.5f, 1.0f }, { orthoSize + (int)cameraPos.x, i + (int)cameraPos.y - 0.5f, 1.0f }, color); //V (LEFT TO RIGHT)
				renderer->RenderLine({ i + (int)cameraPos.x - 0.5f, -orthoSize + (int)cameraPos.y, 1.0f }, { i + (int)cameraPos.x - 0.5f, orthoSize + (int)cameraPos.y, 1.0f }, color); //H (UP TO DOWN)
			}
		}
	}
}
