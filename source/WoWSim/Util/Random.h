#pragma once

#include <optional>

namespace util
{

    class Random
    {
    public:
        static void Initialize(std::optional<uint32_t> seed = std::nullopt);
        static uint64_t Next();
        static uint64_t Next(uint64_t min, uint64_t max);
    };

}