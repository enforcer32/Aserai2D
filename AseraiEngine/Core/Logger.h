
#pragma once

#include <string>
#include <memory>
#include <spdlog/spdlog.h>

namespace Aserai
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

#ifdef ASERAI_ENGINE
	#define ASERAI_LOG_INFO(...)		Aserai::Logger::GetEngineLogger()->info(__VA_ARGS__)
	#define ASERAI_LOG_WARN(...)		Aserai::Logger::GetEngineLogger()->warn(__VA_ARGS__)
	#ifdef ASERAI_ENGINE_DEBUG
		#define ASERAI_LOG_DEBUG(...)	Aserai::Logger::GetEngineLogger()->debug(__VA_ARGS__)
	#else
		#define ASERAI_LOG_DEBUG(...)
	#endif
	#define ASERAI_LOG_ERROR(...)		Aserai::Logger::GetEngineLogger()->error(__VA_ARGS__)
	#define ASERAI_LOG_CRITICAL(...)	(Aserai::Logger::GetEngineLogger()->critical(__VA_ARGS__), throw)
	#define ASERAI_LOG_TRACE(...)		Aserai::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#else
	#define ASERAI_LOG_INFO(...)		Aserai::Logger::GetLogger()->info(__VA_ARGS__)
	#define ASERAI_LOG_WARN(...)		Aserai::Logger::GetLogger()->warn(__VA_ARGS__)
#ifdef ASERAI_DEBUG
	#define ASERAI_LOG_DEBUG(...)		Aserai::Logger::GetLogger()->debug(__VA_ARGS__)
#else
	#define ASERAI_LOG_DEBUG(...)
#endif
	#define ASERAI_LOG_ERROR(...)		Aserai::Logger::GetLogger()->error(__VA_ARGS__)
	#define ASERAI_LOG_CRITICAL(...)	(Aserai::Logger::GetLogger()->critical(__VA_ARGS__), throw)
	#define ASERAI_LOG_TRACE(...)		Aserai::Logger::GetLogger()->trace(__VA_ARGS__)
#endif
