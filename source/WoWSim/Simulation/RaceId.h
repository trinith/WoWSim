#pragma once

#include <cstdint>

namespace sim
{

    enum class RaceId : uint8_t
    {
        Human = 1,
        Orc,
        Dwarf,
        NightElf,
        Undead,
        Tauren,
        Gnome,
        Troll
    };

}