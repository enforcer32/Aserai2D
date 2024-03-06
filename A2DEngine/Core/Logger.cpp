#include "A2DEnginePCH.h"
#include "A2DEngine/Core/Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Aserai2D
{
	void Logger::Init(const std::string& name)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_EngineLogger = spdlog::stdout_color_mt("A2DLogger");
		s_EngineLogger->set_level(spdlog::level::trace);
		s_Logger = spdlog::stdout_color_mt(name);
		s_Logger->set_level(spdlog::level::trace);
	}
}
