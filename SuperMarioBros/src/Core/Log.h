#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#include "Base.h"

class Log
{
public: //Constructors
	Log() = delete;

public: //Public methods
	static void init();

	static Ref<spdlog::logger>& getLogger() { return s_Logger; }
private:
	static Ref<spdlog::logger> s_Logger;
};

struct Loggable
{
	virtual std::string log() const = 0;
};


/* Logging defines */
#ifdef _DEBUG
	#define LOG_TRACE(...)    ::Log::getLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)     ::Log::getLogger()->info(__VA_ARGS__)
	#define LOG_WARN(...)     ::Log::getLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)    ::Log::getLogger()->error(__VA_ARGS__)
#else
	#define LOG_TRACE(...)
	#define LOG_INFO(...)
	#define LOG_WARN(...)
	#define LOG_ERROR(...)
#endif
