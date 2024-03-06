#pragma once

#include "A2DEngine/Scene/SceneCamera.h"

namespace Aserai2D
{
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary; // What if Multiple Scenes
		double Speed;
		bool Fixed;

		CameraComponent(bool primary = false, double speed = 1.0, bool fixed = false)
			: Primary(primary), Speed(speed), Fixed(fixed)
		{
		}

		CameraComponent(SceneCamera camera, bool primary = false, double speed = 1.0, bool fixed = false)
			: Camera(camera), Primary(primary), Speed(speed), Fixed(fixed)
		{
		}
	};
}
