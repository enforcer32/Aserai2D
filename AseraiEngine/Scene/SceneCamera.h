#pragma once

#include "AseraiEngine/Renderer/Camera.h"

namespace Aserai
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();

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

	private:
		void CalculateProjectionMatrix();

	private:
		CameraProjectionType m_ProjectionType;
		float m_AspectRatio;
		float m_OrthographicSize, m_OrthographicNear, m_OrthographicFar;
	};
}
