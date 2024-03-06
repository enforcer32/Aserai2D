#pragma once

#include "A2DEngine/Renderer/Camera.h"
#include "A2DEngine/Core/DeltaTime.h"

namespace Aserai2D
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera();

		void OnUpdate(DeltaTime dt);

		void SetOrthographic(float size, float zNear, float zFar);
		void SetViewport(uint32_t width, uint32_t height);

		CameraProjectionType GetProjectionType() const;
		void SetProjectionType(CameraProjectionType type);

		float GetOrthographicSize() const;
		void SetOrthographicSize(float size);
		float GetOrthographicNear() const;
		void SetOrthographicNear(float zNear);
		float GetOrthographicFar() const;
		void SetOrthographicFar(float zFar);
		float GetOrthographicRotation() const;
		void SetOrthographicRotation(float rotation);
		float GetRotationSpeed() const;
		void SetRotationSpeed(float speed);
		float GetTranslationSpeed() const;
		void SetTranslationSpeed(float speed);

		const glm::mat4& GetTransformMatrix() const;
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetProjectionViewMatrix() const;

	private:
		void CalculateProjectionViewMatrix();

	private:
		CameraProjectionType m_ProjectionType;
		float m_AspectRatio;
		float m_OrthographicSize, m_OrthographicNear, m_OrthographicFar, m_OrthographicRotation;
		float m_TranslationSpeed, m_RotationSpeed;

		glm::vec3 m_Translation, m_Rotation, m_Scale;
		glm::mat4 m_View;
		glm::mat4 m_ProjectionView;
	};
}
