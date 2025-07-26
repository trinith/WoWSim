#pragma once

#include <WoWSimDebugLogging.h>
#include <functional>

namespace sim
{

	class SimulationConsoleLog
	{
	public:
		explicit SimulationConsoleLog(std::function<int64_t()> timeFunction)
			: _timeFunction(std::move(timeFunction))
		{
			// There must always be a time function!
			if (!_timeFunction)
				_timeFunction = []() { return -1; };
		}

		template <typename... TArgs>
		void WriteLine(TArgs&&... args) const
		{
			LOG_WRITELINE("[", _timeFunction(), "] ", std::forward<TArgs>(args)...);
		}

	private:
		std::function<int64_t()> _timeFunction;
	};

}