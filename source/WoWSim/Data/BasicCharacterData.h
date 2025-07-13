#pragma once

#include <Simulation/Attributes.h>
#include <Simulation/ClassId.h>
#include <Simulation/RaceId.h>

#include <unordered_map>

namespace sim::data
{

    static const std::uint32_t MaxLevel = 60;

    static const std::unordered_map<RaceId, PrimaryAttributes> RaceAttributeModifiers{
        { RaceId::Human,    PrimaryAttributes{ 0,  0,  0,  0,  0 } },
        { RaceId::Orc,      PrimaryAttributes{ 3, -3,  2, -3,  3 } },
        { RaceId::Dwarf,    PrimaryAttributes{ 2, -4,  3, -1, -1 } },
        { RaceId::NightElf, PrimaryAttributes{-3,  5, -1,  0,  0 } },
        { RaceId::Undead,   PrimaryAttributes{-1, -2,  1, -2,  5 } },
        { RaceId::Tauren,   PrimaryAttributes{ 5, -5,  2, -5,  2 } },
        { RaceId::Gnome,    PrimaryAttributes{-5,  3, -1,  3,  0 } },
        { RaceId::Troll,    PrimaryAttributes{ 1,  2,  1, -4,  1 } },
    };

}