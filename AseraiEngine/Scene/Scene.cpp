#include "AseraiEnginePCH.h"
#include "AseraiEngine/Scene/Scene.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Aserai
{
	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
	}

	void Scene::OnRuntimeUpdate(DeltaTime dt)
	{
		// ecs->update entities
	}

	void Scene::OnRuntimeRender(DeltaTime dt, const std::shared_ptr<Renderer2D> renderer)
	{
		renderer->BeginRenderer();

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
		transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
		renderer->RenderQuad(transform, { 1.0f, 1.0f, 0.0f, 1.0f });

		renderer->EndRenderer();
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
