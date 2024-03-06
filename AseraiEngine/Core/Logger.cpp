#include "AseraiEnginePCH.h"
#include "Core/Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Aserai
{
	void Logger::Init(const std::string& name)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_EngineLogger = spdlog::stdout_color_mt("AseraiEngineLogger");
		s_EngineLogger->set_level(spdlog::level::trace);
		s_Logger = spdlog::stdout_color_mt(name);
		s_Logger->set_level(spdlog::level::trace);
	}
}
