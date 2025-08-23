#pragma once
#include <cstdint>

namespace sim
{
    enum class WeaponType : uint8_t
    {
        Unarmed = 0,

        Sword1h,
        Mace1h,
        Axe1h,
        Dagger,
        FistWeapon,

        Sword2h,
        Mace2h,
        Axe2h,
        Polearm,
        Staff,

        Bow,
        Crossbow,
        Gun,

        Thrown,
        Wand,
    };
}