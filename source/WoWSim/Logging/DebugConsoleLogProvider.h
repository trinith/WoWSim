#pragma once

#if defined(DEBUG_LOGGING)

#include <iostream>

namespace logging
{
	class DebugConsoleLogProvider
	{
	public:
		template <typename TType>
		static void Write(TType t)
		{
			std::cout << t;
		}
	};
}

#endif