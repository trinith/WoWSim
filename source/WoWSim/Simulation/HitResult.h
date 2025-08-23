#pragma once

namespace sim
{

    enum class MeleeHitResult
    {
        Miss = 0,
        Dodge,
        Parry,
        Glancing,
        Block,
        Crit,
        Crushing,
        Hit,
    };

}