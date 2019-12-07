#pragma once
#include "Hazel/Core/Core.h"

#ifdef HZ_PROFILE
#include <filesystem>
#endif

#ifdef HZ_PLATFORM_WINDOWS
#include "Windows.h"

#ifdef HZ_DEBUG
#else
#include "spdlog/sinks/null_sink.h"
#endif

extern Hazel::Application* Hazel::CreateApplication();

// Entry point if App is compiled with subsystem:console
int main(int argc, char** argv) {
	Hazel::Log::Init();

	std::filesystem::path binDirectory = std::filesystem::path(argv[0]).remove_filename();

	HZ_PROFILE_BEGIN_SESSION("Startup", (binDirectory / "HazelProfile-Startup.json").string());
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", (binDirectory / "HazelProfile-Runtime.json").string());
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", (binDirectory / "HazelProfile-Shutdown.json").string());
	delete app;
	HZ_PROFILE_END_SESSION();
}


// Entry point if App is compiled with subsystem:windows
int wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {

#ifdef HZ_DEBUG
	// DEBUG build => use default logging to console window
	AllocConsole();
	Hazel::Log::Init();

	// You could also send logging to the msvc output window (without creating extra console window)
	// If you prefer this option, then do the following (instead of AllocConsole(); Hazel::Log::Init();)
	//Hazel::Log::Init(spdlog::create<spdlog::sinks::msvc_sink_mt>("HAZEL"), spdlog::create<spdlog::sinks::msvc_sink_mt>("APP"));

#else
	// non DEBUG build => logging goes nowhere (and do not create extra console window)
	Hazel::Log::Init(spdlog::create<spdlog::sinks::null_sink_mt>("HAZEL"), spdlog::create<spdlog::sinks::null_sink_mt>("APP"));
#endif

#ifdef HZ_PROFILE
	HMODULE hModule = GetModuleHandleW(nullptr);
	TCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);
	std::filesystem::path binDirectory = std::filesystem::path(path).remove_filename();
#endif

	HZ_PROFILE_BEGIN_SESSION("Startup", (binDirectory / "HazelProfile-Startup.json").string());
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", (binDirectory / "HazelProfile-Runtime.json").string());
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", (binDirectory / "HazelProfile-Shutdown.json").string());
	delete app;
	HZ_PROFILE_END_SESSION();

	return 0;
}
#endif
