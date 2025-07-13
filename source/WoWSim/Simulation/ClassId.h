#pragma once

#include <cstdint>

namespace sim
{

    enum class ClassId : uint8_t
    {
        Warrior = 1,
        Paladin,
        Hunter,
        Rogue,
        Priest,
        DeathKnight,
        Shaman,
        Mage,
        Warlock,
        Monk,
        Druid
    };

}