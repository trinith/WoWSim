#pragma once

namespace sim
{

    enum class DamageType
    {
        Physical = 0x1,
        Holy = 0x2,
        Fire = 0x4,
        Nature = 0x8,
        Frost = 0x10,
        Shadow = 0x20,
        Arcane = 0x40,
    };

}