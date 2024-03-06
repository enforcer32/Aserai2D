#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Aserai
{
	struct TransformComponent
	{
		glm::vec3 Translation;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		TransformComponent(const glm::vec3& translation = glm::vec3( 0.0f, 0.0f, 0.0f ), const glm::vec3& rotation = glm::vec3(0.0, 0.0, 1.0), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
			: Translation(translation), Rotation(rotation), Scale(scale)
		{
		}

		glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), Translation) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), Rotation) * glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}
