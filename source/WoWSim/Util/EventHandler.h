#pragma once

#include <functional>
#include <string>

namespace util
{

	template <typename TSender, typename... TArgs>
	class EventHandler
	{
	public:
		using HandlerFunction = std::function<void(const TSender&, TArgs...)>;

		void operator+=(HandlerFunction handler)
		{
			if (handler)
			{
				std::string handlerKey = GetKeyForHandler(handler);
				auto findResult = _handlers.find(handlerKey);
				if (findResult == _handlers.end())
					_handlers.emplace(handlerKey, HandlerInfo{ std::move(handler), 1 });
				else
					findResult->second.count++;
			}
		}

		void operator-=(HandlerFunction handler)
		{
			if (handler)
			{
				std::string handlerKey = GetKeyForHandler(handler);
				auto findResult = _handlers.find(handlerKey);
				if (findResult != _handlers.end())
				{
					--findResult->second.count;

					if (findResult->second.count == 0)
						_handlers.erase(handlerKey);
				}
			}
		}

		void operator()(const TSender& sender, TArgs... args) const
		{
			for (auto& [_, value] : _handlers)
			{
				for (size_t i = 0; i < value.count; ++i)
					value.function(sender, args...);
			}
		}

		void Clear()
		{
			_handlers.clear();
		}


		explicit operator bool() const
		{
			return !_handlers.empty();
		}

	private:
		struct HandlerInfo
		{
			HandlerFunction function;
			size_t count = 1;
		};

		std::string GetKeyForHandler(const HandlerFunction& handler)
		{
			auto handlerTarget = handler.target<void(*)(const TSender&, TArgs...)>();
			if (handlerTarget)
			{
				return std::to_string(reinterpret_cast<size_t>(*handlerTarget));
			}
			else
			{
				return handler.target_type().name();
			}
		}

		std::unordered_map<std::string, HandlerInfo> _handlers;
	};

}