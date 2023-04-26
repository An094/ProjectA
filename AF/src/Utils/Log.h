#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace EngineCore {
	namespace Utils
	{
		class Log
		{
		public:
			Log() = delete;
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_EngineLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		private:
			static std::shared_ptr<spdlog::logger> s_EngineLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
		};

	}
}
		//Engine log macros
#define ENGINE_ERROR(...)	EngineCore::Utils::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_WARN(...)	EngineCore::Utils::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_INFO(...)	EngineCore::Utils::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_TRACE(...)	EngineCore::Utils::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_FATAL(...)	EngineCore::Utils::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define CLIENT_ERROR(...)		EngineCore::Utils::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_WARN(...)		EngineCore::Utils::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_INFO(...)		EngineCore::Utils::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_TRACE(...)		EngineCore::Utils::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_FATAL(...)		EngineCore::Utils::Log::GetClientLogger()->fatal(__VA_ARGS__)