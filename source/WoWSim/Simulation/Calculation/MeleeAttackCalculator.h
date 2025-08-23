#pragma once

#include <Simulation/HitResult.h>
#include <Simulation/Character/Character.h>

#include <array>
#include <functional>

namespace sim
{

    class MeleeAttackCalculator
    {
    public:
        static MeleeHitResult DetermineHitResult(float rollBase, const sim::Character& attacker, const sim::Character& target);
    };
}