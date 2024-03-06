
#pragma once

#include <string>
#include <memory>
#include <spdlog/spdlog.h>

namespace Aserai2D
{
	class Logger
	{
	public:
		static void Init(const std::string& name = "AseraiLogger");
		inline static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger> GetLogger() { return s_Logger; }

	private:
		inline static std::shared_ptr<spdlog::logger> s_EngineLogger;
		inline static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#ifdef ASERAI2D_ENGINE
	#define ASERAI_LOG_INFO(...)		Aserai2D::Logger::GetEngineLogger()->info(__VA_ARGS__)
	#define ASERAI_LOG_WARN(...)		Aserai2D::Logger::GetEngineLogger()->warn(__VA_ARGS__)
	#ifdef ASERAI2D_ENGINE_DEBUG
		#define ASERAI_LOG_DEBUG(...)	Aserai2D::Logger::GetEngineLogger()->debug(__VA_ARGS__)
	#else
		#define ASERAI_LOG_DEBUG(...)
	#endif
	#define ASERAI_LOG_ERROR(...)		Aserai2D::Logger::GetEngineLogger()->error(__VA_ARGS__)
	#define ASERAI_LOG_CRITICAL(...)	(Aserai2D::Logger::GetEngineLogger()->critical(__VA_ARGS__), throw)
	#define ASERAI_LOG_TRACE(...)		Aserai2D::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#else
	#define ASERAI_LOG_INFO(...)		Aserai2D::Logger::GetLogger()->info(__VA_ARGS__)
	#define ASERAI_LOG_WARN(...)		Aserai2D::Logger::GetLogger()->warn(__VA_ARGS__)
#ifdef ASERAI2D_DEBUG
	#define ASERAI_LOG_DEBUG(...)		Aserai2D::Logger::GetLogger()->debug(__VA_ARGS__)
#else
	#define ASERAI_LOG_DEBUG(...)
#endif
	#define ASERAI_LOG_ERROR(...)		Aserai2D::Logger::GetLogger()->error(__VA_ARGS__)
	#define ASERAI_LOG_CRITICAL(...)	(Aserai2D::Logger::GetLogger()->critical(__VA_ARGS__), throw)
	#define ASERAI_LOG_TRACE(...)		Aserai2D::Logger::GetLogger()->trace(__VA_ARGS__)
#endif
