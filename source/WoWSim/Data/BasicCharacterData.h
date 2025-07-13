#pragma once

#include <Simulation/Attributes/Attributes.h>
#include <Simulation/ClassId.h>
#include <Simulation/RaceId.h>

#include <unordered_map>

namespace sim::data
{

    static const std::uint32_t MaxLevel = 60;

    static const std::unordered_map<RaceId, Attributes> RaceAttributeModifiers{
        { RaceId::Human,    Attributes{ 0,  0,  0,  0,  0 } },
        { RaceId::Orc,      Attributes{ 3, -3,  2, -3,  3 } },
        { RaceId::Dwarf,    Attributes{ 2, -4,  3, -1, -1 } },
        { RaceId::NightElf, Attributes{-3,  5, -1,  0,  0 } },
        { RaceId::Undead,   Attributes{-1, -2,  1, -2,  5 } },
        { RaceId::Tauren,   Attributes{ 5, -5,  2, -5,  2 } },
        { RaceId::Gnome,    Attributes{-5,  3, -1,  3,  0 } },
        { RaceId::Troll,    Attributes{ 1,  2,  1, -4,  1 } },
    };

}