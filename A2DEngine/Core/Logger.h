#pragma once

#include <spdlog/spdlog.h>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

namespace Aserai2D
{
	class Logger
	{
	public:
		static void Init(const std::string& name = "AseraiLogger");
		inline static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger> GetLogger() { return s_Logger; }

		static void SaveLastLog();
		static void Clear();
		static const std::vector<std::string>& GetLogs();

	private:
		inline static std::shared_ptr<spdlog::logger> s_EngineLogger;
		inline static std::shared_ptr<spdlog::logger> s_Logger;
		inline static std::vector<std::string> s_Logs;
		inline static std::ostringstream s_Stream;
	};
}

#ifdef ASERAI2D_ENGINE
	#define ASERAI_LOG_INFO(...)		(Aserai2D::Logger::GetEngineLogger()->info(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
	#define ASERAI_LOG_WARN(...)		(Aserai2D::Logger::GetEngineLogger()->warn(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
	#ifdef ASERAI2D_ENGINE_DEBUG
		#define ASERAI_LOG_DEBUG(...)	(Aserai2D::Logger::GetEngineLogger()->debug(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
	#else
		#define ASERAI_LOG_DEBUG(...)
	#endif
	#define ASERAI_LOG_ERROR(...)		(Aserai2D::Logger::GetEngineLogger()->error(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
	#define ASERAI_LOG_CRITICAL(...)	(Aserai2D::Logger::GetEngineLogger()->critical(__VA_ARGS__), Aserai2D::Logger::SaveLastLog(), throw)
	#define ASERAI_LOG_TRACE(...)		(Aserai2D::Logger::GetEngineLogger()->trace(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
#else
	#define ASERAI_LOG_INFO(...)		(Aserai2D::Logger::GetLogger()->info(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
	#define ASERAI_LOG_WARN(...)		(Aserai2D::Logger::GetLogger()->warn(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
#ifdef ASERAI2D_DEBUG
	#define ASERAI_LOG_DEBUG(...)		(Aserai2D::Logger::GetLogger()->debug(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
#else
	#define ASERAI_LOG_DEBUG(...)
#endif
	#define ASERAI_LOG_ERROR(...)		(Aserai2D::Logger::GetLogger()->error(__VA_ARGS__), Aserai2D::Logger::SaveLastLog())
	#define ASERAI_LOG_CRITICAL(...)	(Aserai2D::Logger::GetLogger()->critical(__VA_ARGS__), Aserai2D::Logger::SaveLastLog(), throw)
	#define ASERAI_LOG_TRACE(...)		(Aserai2D::Logger::GetLogger()->trace(__VA_ARGS__), Aserai2D::Logger::SaveLastLog(), __VA_ARGS__))
#endif
