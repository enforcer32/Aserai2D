#include "A2DEnginePCH.h"
#include "A2DEngine/Editor/EditorCamera.h"
#include "A2DEngine/Input/InputManager.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Aserai2D
{
	EditorCamera::EditorCamera()
		: m_ProjectionType(CameraProjectionType::Orthographic), m_AspectRatio(1.3f),
		m_OrthographicSize(10.0f), m_OrthographicNear(-1.0f), m_OrthographicFar(1.0f), m_OrthographicRotation(0.0f),
		m_TranslationSpeed(5.0f), m_RotationSpeed(90.0f),
		m_Translation({ 0.0f, 0.0f, 0.0f }), m_Rotation({ 0.0f, 0.0f, 1.0f }), m_Scale({ 1.0f, 1.0f, 1.0f })
	{
		CalculateProjectionViewMatrix();
	}

	void EditorCamera::OnUpdate(DeltaTime dt)
	{
		if (InputManager::IsKeyPressed(KeyCode::LeftControl))
		{
			bool flag = false;

			if (InputManager::IsKeyPressed(KeyCode::W))
			{
				m_Translation.y += m_TranslationSpeed * dt;
				flag = true;
			}

			if (InputManager::IsKeyPressed(KeyCode::S))
			{
				m_Translation.y -= m_TranslationSpeed * dt;
				flag = true;
			}

			if (InputManager::IsKeyPressed(KeyCode::A))
			{
				m_Translation.x -= m_TranslationSpeed * dt;
				flag = true;
			}

			if (InputManager::IsKeyPressed(KeyCode::D))
			{
				m_Translation.x += m_TranslationSpeed * dt;
				flag = true;
			}

			if (InputManager::IsKeyPressed(KeyCode::Q))
			{
				m_OrthographicRotation += m_RotationSpeed * dt;
				flag = true;
			}

			if (InputManager::IsKeyPressed(KeyCode::E))
			{
				m_OrthographicRotation -= m_RotationSpeed * dt;
				flag = true;
			}

			if (InputManager::IsMouseScrollingUp())
			{
				m_OrthographicSize -= 1;
				flag = true;
			}

			if (InputManager::IsMouseScrollingDown())
			{
				m_OrthographicSize += 1;
				flag = true;
			}

			if(flag)
				CalculateProjectionViewMatrix();
		}
	}

	void EditorCamera::SetOrthographic(float size, float zNear, float zFar)
	{
		m_ProjectionType = CameraProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = zNear;
		m_OrthographicFar = zFar;
		CalculateProjectionViewMatrix();
	}

	void EditorCamera::SetViewport(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		CalculateProjectionViewMatrix();
	}

	CameraProjectionType EditorCamera::GetProjectionType() const
	{
		return m_ProjectionType;
	}

	void EditorCamera::SetProjectionType(CameraProjectionType type)
	{
		m_ProjectionType = type;
		CalculateProjectionViewMatrix();
	}

	float EditorCamera::GetOrthographicSize() const
	{
		return m_OrthographicSize;
	}

	void EditorCamera::SetOrthographicSize(float size)
	{
		m_OrthographicSize = size;
		CalculateProjectionViewMatrix();
	}

	float EditorCamera::GetOrthographicNear() const
	{
		return m_OrthographicNear;
	}

	void EditorCamera::SetOrthographicNear(float zNear)
	{
		m_OrthographicNear = zNear;
		CalculateProjectionViewMatrix();
	}

	float EditorCamera::GetOrthographicFar() const
	{
		return m_OrthographicFar;
	}

	void EditorCamera::SetOrthographicFar(float zFar)
	{
		m_OrthographicFar = zFar;
		CalculateProjectionViewMatrix();
	}

	float EditorCamera::GetOrthographicRotation() const
	{
		return m_OrthographicRotation;
	}

	void EditorCamera::SetOrthographicRotation(float rotation)
	{
		m_OrthographicRotation = rotation;
		CalculateProjectionViewMatrix();
	}

	float EditorCamera::GetRotationSpeed() const
	{
		return m_RotationSpeed;
	}

	void EditorCamera::SetRotationSpeed(float speed)
	{
		m_RotationSpeed = speed;
	}
	
	float EditorCamera::GetTranslationSpeed() const
	{
		return m_TranslationSpeed;
	}
	
	void EditorCamera::SetTranslationSpeed(float speed)
	{
		m_TranslationSpeed = speed;
	}

	const glm::mat4& EditorCamera::GetTransformMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), m_Translation) * glm::rotate(glm::mat4(1.0f), glm::radians(m_OrthographicRotation), m_Rotation) * glm::scale(glm::mat4(1.0f), m_Scale);
	}

	const glm::mat4& EditorCamera::GetViewMatrix() const
	{
		return m_View;
	}

	const glm::mat4& EditorCamera::GetProjectionViewMatrix() const
	{
		return m_ProjectionView;
	}

	void EditorCamera::CalculateProjectionViewMatrix()
	{
		if (m_ProjectionType == CameraProjectionType::Orthographic)
			m_Projection = glm::ortho(-m_AspectRatio * m_OrthographicSize * 0.5f, m_AspectRatio * m_OrthographicSize * 0.5f, -m_OrthographicSize * 0.5f, m_OrthographicSize * 0.5f, m_OrthographicNear, m_OrthographicFar);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Translation) * glm::rotate(glm::mat4(1.0f), glm::radians(m_OrthographicRotation), m_Rotation) * glm::scale(glm::mat4(1.0f), m_Scale);
		m_View = glm::inverse(transform);
		m_ProjectionView = m_Projection * m_View;
	}
}
