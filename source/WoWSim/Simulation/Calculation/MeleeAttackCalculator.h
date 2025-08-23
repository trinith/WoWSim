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

        static float CalculateMissChance(const sim::Character& attacker, const sim::Character& target);
        static float CalculateDodgeChance(const sim::Character& attacker, const sim::Character& target);
        static float CalculateParryChance(const sim::Character& attacker, const sim::Character& target);
        static float CalculateGlancingChance(const sim::Character& attacker, const sim::Character& target);
        static float CalculateBlockChance(const sim::Character& attacker, const sim::Character& target);
        static float CalculateCritChance(const sim::Character& attacker, const sim::Character& target);
        static float CalculateCrushingBlowChance(const sim::Character& attacker, const sim::Character& target);
    };
}