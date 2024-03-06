#pragma once

#include "AseraiEngine/Scene/SceneCamera.h"

namespace Aserai
{
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary;
		bool Fixed;

		CameraComponent(bool primary = false, bool fixed = false)
			: Primary(primary), Fixed(fixed)
		{
		}

		CameraComponent(SceneCamera camera, bool primary = false, bool fixed = false)
			: Camera(camera), Primary(primary), Fixed(fixed)
		{
		}
	};
}
