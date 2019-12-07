#include "hzpch.h"
#include "Hazel/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Hazel {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init(Ref<spdlog::logger> coreLogger, Ref<spdlog::logger> clientLogger) {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = std::move(coreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = std::move(clientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}
