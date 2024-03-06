#include "A2DEnginePCH.h"
#include "A2DEngine/Scene/SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Aserai2D
{
	SceneCamera::SceneCamera()
		: m_ProjectionType(CameraProjectionType::Orthographic), m_AspectRatio(1.3f),
		m_OrthographicSize(10.0f), m_OrthographicNear(-1.0f), m_OrthographicFar(1.0f)
	{
		CalculateProjectionMatrix();
	}

	void SceneCamera::SetOrthographic(float size, float zNear, float zFar)
	{
		m_ProjectionType = CameraProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = zNear;
		m_OrthographicFar = zFar;
		CalculateProjectionMatrix();
	}

	void SceneCamera::SetViewport(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		CalculateProjectionMatrix();
	}

	CameraProjectionType SceneCamera::GetProjectionType() const
	{ 
		return m_ProjectionType; 
	}

	void SceneCamera::SetProjectionType(CameraProjectionType type)
	{ 
		m_ProjectionType = type;
		CalculateProjectionMatrix();
	}

	float SceneCamera::GetOrthographicSize() const
	{ 
		return m_OrthographicSize;
	}

	void SceneCamera::SetOrthographicSize(float size)
	{ 
		m_OrthographicSize = size; 
		CalculateProjectionMatrix();
	}

	float SceneCamera::GetOrthographicNear() const 
	{ 
		return m_OrthographicNear;
	}

	void SceneCamera::SetOrthographicNear(float zNear) 
	{ 
		m_OrthographicNear = zNear;
		CalculateProjectionMatrix();
	}

	float SceneCamera::GetOrthographicFar() const 
	{ 
		return m_OrthographicFar;
	}

	void SceneCamera::SetOrthographicFar(float zFar) 
	{ 
		m_OrthographicFar = zFar; 
		CalculateProjectionMatrix();
	}

	void SceneCamera::CalculateProjectionMatrix()
	{
		if (m_ProjectionType == CameraProjectionType::Orthographic)
			m_Projection = glm::ortho(-m_AspectRatio * m_OrthographicSize * 0.5f, m_AspectRatio * m_OrthographicSize * 0.5f, -m_OrthographicSize * 0.5f, m_OrthographicSize * 0.5f, m_OrthographicNear, m_OrthographicFar);
	}
}
