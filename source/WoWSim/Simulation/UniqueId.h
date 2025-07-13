#pragma once
#include <type_traits>
#include <unordered_map>

namespace sim
{

    class UniqueId
    {
    public:
        enum class Type
        {
            Character,
        };

        template <auto EnumVal>
            requires std::is_same_v<decltype(EnumVal), Type>
        static uint64_t Next()
        {
            if (_nextId.find(EnumVal) == _nextId.end())
                _nextId.emplace(EnumVal, 0u);

            return _nextId.at(EnumVal)++;
        }
    private:
        inline static std::unordered_map<Type, uint64_t> _nextId{};
    };

}