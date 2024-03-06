#pragma once

#include "AseraiEngine/Input/InputCodes.h"

namespace Aserai
{
	struct KeyboardMovementComponent
	{
		KeyCode LeftKey;
		KeyCode RightKey;
		KeyCode UpKey;
		KeyCode DownKey;
		double Speed;
		bool Fixed;
		bool UpdateRotation2D;

		KeyboardMovementComponent(KeyCode leftKey = KeyCode::A, KeyCode rightKey = KeyCode::D, KeyCode upKey = KeyCode::W, KeyCode downKey = KeyCode::S, double speed = 1.0, bool fixed = false, bool updateRotation2D = false)
			: LeftKey(leftKey), RightKey(rightKey), UpKey(upKey), DownKey(downKey), Speed(speed), Fixed(false), UpdateRotation2D(updateRotation2D)
		{
		}

		KeyboardMovementComponent(double speed, bool updateRotation2D = false, KeyCode leftKey = KeyCode::A, KeyCode rightKey = KeyCode::D, KeyCode upKey = KeyCode::W, KeyCode downKey = KeyCode::S, bool fixed = false)
			: LeftKey(leftKey), RightKey(rightKey), UpKey(upKey), DownKey(downKey), Speed(speed), Fixed(false), UpdateRotation2D(updateRotation2D)
		{
		}
	};
}
