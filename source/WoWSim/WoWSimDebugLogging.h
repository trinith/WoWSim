#pragma once

#if defined(_DEBUG) && !defined(DEBUG_LOGGING)
	#define DEBUG_LOGGING
#endif

#if defined(DEBUG_LOGGING)
#include <Logging/DebugConsoleLogProvider.h>
#include <Logging/DebugLogManager.h>

using Logger = logging::DebugLogManager<logging::DebugConsoleLogProvider>;

#define LOG_WRITE(...) Logger::Write(__VA_ARGS__)
#define LOG_WRITELINE(...) Logger::WriteLine(__VA_ARGS__)
#define LOG_INDENT(scopeVar) auto scopeVar = Logger::CreateIndentScope()

#else

#define LOG_WRITE(...)
#define LOG_WRITELINE(...)
#define LOG_INDENT(scopeVar)

#endif