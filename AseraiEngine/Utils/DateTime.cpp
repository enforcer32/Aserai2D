#include "AseraiEnginePCH.h"
#include "Utils/DateTime.h"

#include <GLFW/glfw3.h>

namespace Aserai
{
	double DateTime::GetTimeSeconds()
	{
		return glfwGetTime();
	}

	double DateTime::GetTimeMilliSeconds()
	{
		return glfwGetTime() * 1000;
	}
}
