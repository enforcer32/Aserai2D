#pragma once

#include <glm/glm.hpp>

namespace Aserai2D
{
	enum class CameraProjectionType
	{
		Orthographic = 0,
		Perspective = 1
	};

	class Camera
	{
	public:
		Camera() = default;
		~Camera() = default;

		Camera(const glm::mat4& projection)
			: m_Projection(projection)
		{}

		inline const glm::mat4& GetProjection() const { return m_Projection; }

	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}
